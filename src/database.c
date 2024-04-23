#ifndef DEBUG
#include "database.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 用于打开文件的宏
*/
#define _file_safe_open(attr, file, mode, ret) \
    FILE *(attr) = fopen((file), (mode)); \
    if((attr) == NULL){ \
        return ret; \
    }


/**
 * @brief 用于定位表头的宏
*/
#define _table_word_check(fp, info, word) \
    int col_position = -1; \
    fseek((fp), (info).start, SEEK_SET); \
    for(int i = 0; i < (count); i++){ \
        char temp_str[256]; \
        fscanf((fp), "%s", temp_str); \
        if(strcmp(temp_str, (word)) == 0){ \
            col_position = i; \
        } \
    }


/**
 * @brief 用于定位前后的宏
*/
#define _table_word_local(fp, info, word) \
    int col_before = 0, col_after = 0, col_local = 0; \
    fseek((fp), (info).start + (info).lin_width + 2, SEEK_SET); \
    for(int i = 0; i < (count); i++){ \
        int temp_int; \
        fscanf((fp), "%d", &temp_int); \
        if(i < col_position){ \
            col_before += temp_int; \
        } else if(i > col_position){ \
            col_after += temp_int; \
        } else { \
            col_local = temp_int; \
        } \
    } \


/**
 * @brief 在文件中移动指定的字节数
 * @param _file 文件指针
 * @param _offset 移动的字节数
 * @return 0代表成功，其他代表失败
*/
inline int fmove(FILE *_file, long _offset){
    if(_offset <= 0 || _offset > 16){
        return fseek(_file, _offset, SEEK_CUR);
    }
    for(long i=0; i<_offset; i++){
        fgetc(_file);
    }
    return 0;
}


/**
 * @brief 在文件中插入字符串
 * @param _file 文件指针
 * @param _str 要插入的字符串
 * @return 0代表成功，其他代表失败
*/
int finsert(FILE *_file, const str _str){
    int start_cursor = ftell(_file);
    fseek(_file, 0, SEEK_END);
    int end_cursor = ftell(_file);
    char *buffer = (char*)malloc(end_cursor - start_cursor + 8);
    if(buffer == NULL){
        return 1;
    }
    fseek(_file, start_cursor, SEEK_SET);
    fread(buffer, 1, end_cursor - start_cursor, _file);
    fseek(_file, start_cursor, SEEK_SET);
    fprintf(_file, "%s", _str);
    fwrite(buffer, 1, end_cursor - start_cursor, _file);
    free(buffer);
    return 0;
}


/**
 * @brief 获取表的信息
 * @param _fp 文件指针
 * @return 表的信息
*/
table_info table_get_info(FILE* _fp){
    table_info _table_info;
    _table_info.head = ftell(_fp);
    fscanf(_fp, "%s%d%d", _table_info.table_name, &(_table_info.lin_width), &(_table_info.col_count));
    _table_info.start = ftell(_fp) + 2;
    fseek(_fp, _table_info.head, SEEK_SET);
    return _table_info;
}


/**
 * @brief 连接到数据库
 * @param _file_name 数据库文件名
 * @return 数据库对象
*/
db db_connect(const str _file_name){
    db _db;
    strcpy(_db._file_name, _file_name);
    _db._master = map_create();
    FILE* file_ptr = fopen(_file_name, "rb");
    if(file_ptr == NULL){
        FILE* file_ptr = fopen(_file_name, "wb");
        fprintf(file_ptr, "master 24 2\r\n%16s%8s\r\n%16d%8d\r\n%16s%8d\r\n======\r\n",
                          "table", "width", 16, 8, "master", 24);
        fclose(file_ptr);
        map_set(&(_db._master), "master", 24);
        return _db;
    }
    char table_name[256];
    int table_width = 0, file_cur = 65;
    while(1){
        fseek(file_ptr, file_cur, SEEK_SET);
        char c = fgetc(file_ptr);
        if(c == '=' || c == EOF){
            break;
        }
        fscanf(file_ptr, "%s%d", table_name, &table_width);
        map_set(&(_db._master), table_name, table_width);
        file_cur += (24 + 2);
    }
    fclose(file_ptr);
    return _db;
}


/**
 * @brief 在数据库中创建表
 * @param _db 数据库对象
 * @param _table 表名
 * @param _columns 列信息
*/ 
void db_insert_table(db* _db, const str _table, const map _columns){
    if(map_get(&(_db->_master), _table) != 0){
        return;
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb+", );
    int col_count = 0, lin_width = 0;
    for(int i = 0; i < _columns._capacity && _columns.keys[i] != NULL; i++){
        col_count++;
        lin_width += _columns.values[i];
    }
    map_set(&(_db->_master), _table, lin_width);
    _table_skip_to_next(file_ptr);
    fmove(file_ptr, -8);
    char format[256];
    sprintf(format, "%16s%8d\r\n", _table, lin_width);
    finsert(file_ptr, format);
    fclose(file_ptr);
    file_ptr = fopen(_db->_file_name, "ab");
    fprintf(file_ptr, "%s %d %d\r\n", _table, lin_width, col_count);
    for(int i=0; i<col_count; i++){
        sprintf(format, "%%%ds", _columns.values[i]);
        fprintf(file_ptr, format, _columns.keys[i]);
    }
    fprintf(file_ptr, "\r\n");
    for(int i=0; i<col_count; i++){
        sprintf(format, "%%%dd", _columns.values[i]);
        fprintf(file_ptr, format, _columns.values[i]);
    }
    fprintf(file_ptr, "\r\n======\r\n");
    fclose(file_ptr);
}


/**
 * @brief 在数据库中插入行
 * @param _db 数据库对象
 * @param _table 表名
 * @param _values 值
*/
void db_insert_lin(db* _db, const str _table, list _values){
    if(map_get(&(_db->_master), _table) == 0){
        return;
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb+", );
    _table_skip_to_table(file_ptr, _table);
    table_info info = table_get_info(file_ptr);
    fseek(file_ptr, info.start, SEEK_SET);
    fmove(file_ptr, info.lin_width+2);
    char format[256] = {}, result[65536] = {};
    int result_len = 0, each_width = 0;
    for(int i=0; i<info.col_count; i++){
        fscanf(file_ptr, "%d", &each_width);
        sprintf(format, "%%%ds", each_width);
        sprintf(result + result_len, format, list_get(str, &_values, i));
        result_len += each_width;
    }
    fseek(file_ptr, info.head, SEEK_SET);
    _table_skip_to_next(file_ptr);
    fmove(file_ptr, -8);
    sprintf(result + result_len, "\r\n");
    finsert(file_ptr, result);
    fclose(file_ptr);
}

/**
 * @brief 在数据库中删除表
 * @param _db 数据库对象
 * @param _table 表名
*/
void db_remove_table(db* _db, const str _table){
    if(map_get(&(_db->_master), _table) == 0){
        return;
    }
    map_remove(&(_db->_master), _table);
    _file_safe_open(file_ptr, _db->_file_name, "rb+", );
    table_info info = table_get_info(file_ptr);
    fseek(file_ptr, info.start, SEEK_SET);
    fmove(file_ptr, (info.lin_width + 2)*2);
    char temp_char, temp_str[256];
    while(1){
        temp_char = fgetc(file_ptr);
        if(temp_char == '='){
            break;
        }
        fscanf(file_ptr, "%s", temp_str);
        if(strcmp(temp_str, _table) == 0){
            fmove(file_ptr, -16);
            fprintf(file_ptr, "%24s", "");
            break;
        } else {
            fmove(file_ptr, 10);
        }
    }
    fclose(file_ptr);
}


/**
 * @brief 在数据库中删除行
 * @param _db 数据库对象
 * @param _table 表名
 * @param _oid 行号
*/ 
void db_remove_lin(db* _db, const str _table, const int _oid){
    if(map_get(&(_db->_master), _table) == 0){
        return;
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb+", );
    _table_skip_to_table(file_ptr, _table);
    table_info info = table_get_info(file_ptr);
    _table_skip_to_position(file_ptr, 1, _oid);
    char format[256];
    sprintf(format, "%%%ds", info.lin_width);
    fprintf(file_ptr, format, "");
    fclose(file_ptr);
}


/**
 * @brief 在数据库中提取出一个数据
 * @param _db 数据库对象
 * @param _table 表名
 * @param _column 列名
 * @param _oid 行号
*/
str db_select(db* _db, const str _table, const str _column, const int _oid){
    if(map_get(&(_db->_master), _table) == 0){
        return NULL;
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb", NULL);
    _table_skip_to_table(file_ptr, _table);
    table_info info = table_get_info(file_ptr);
    _table_word_check(file_ptr, info, _column);
    if(col_position == -1){
        return NULL;
    }
    _table_word_local(file_ptr, info, _column);
    fseek(file_ptr, info.head, SEEK_SET);
    _table_skip_to_position(file_ptr, col_position, _oid);
    char result[256];
    fscanf(file_ptr, "%s", result);
    fclose(file_ptr);
    return string(result);
}


/**
 * @brief 在数据库中提取出一列数据
 * @param _db 数据库对象
 * @param _table 表名
 * @param _column 列名
*/
list db_select_col(db* _db, const str _table, const str _column){
    if(map_get(&(_db->_master), _table) == 0){
        return list_create(void);
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb", list_create(void));
    _table_skip_to_table(file_ptr, _table);
    table_info info = table_get_info(file_ptr);
    _table_word_check(file_ptr, info, _column);
    if(col_position == -1){
        return list_create(void);
    }
    _table_word_local(file_ptr, info, _column);
    char temp_char, temp_str[256];
    list result = list_create(str);
    fseek(file_ptr, info.start, SEEK_SET);
    fmove(file_ptr, (info.lin_width+2)*2);
    for(int oid=0; ; oid++){
        temp_char = fgetc(file_ptr);
        if(temp_char == '='){
            break;
        }
        fmove(file_ptr, col_before);
        fscanf(file_ptr, "%s", temp_str);
        list_append(&result, string(temp_str));
        fmove(file_ptr, col_after+2);
    }
    fclose(file_ptr);
    return result;
}


/**
 * @brief 在数据库中提取出一行数据
 * @param _db 数据库对象
 * @param _table 表名
 * @param _oid 行号
*/
dict db_select_lin(db* _db, const str _table, const int _oid){
    if(map_get(&(_db->_master), _table) == 0){
        return dict_create();
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb", dict_create());
    _table_skip_to_table(file_ptr, _table);
    table_info info = table_get_info(file_ptr);
    dict result = dict_create();
    fseek(file_ptr, info.start, SEEK_SET);
    char temp_str[256];
    for(int i=0; i<info.col_count; i++){
        fscanf(file_ptr, "%s", temp_str);
        dict_set(&result, temp_str, "");
    }
    fseek(file_ptr, info.start, SEEK_SET);
    fmove(file_ptr, (info.lin_width+2)*2);
    fmove(file_ptr, (info.lin_width+2)*(_oid-1));
    for(int i=0; i<info.col_count; i++){
        fscanf(file_ptr, "%s", temp_str);
        dict_set(&result, result.keys[i], temp_str);
    }
    return result;
}


/**
 * 
*/
int db_select_where(db* _db, const str _table, const str _column, const str _value){
    if(map_get(&(_db->_master), _table) == 0){
        return 0;
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb", 0);
    _table_skip_to_table(file_ptr, _table);
    table_info info = table_get_info(file_ptr);
    _table_word_check(file_ptr, info, _column);
    if(col_position == -1){
        return 0;
    }
    _table_word_local(file_ptr, info, _column);
    char result[256] = {}, first = '';
    fseek(file_ptr, info.start, SEEK_SET);
    fmove(file_ptr, (info.lin_width+2)*2);
    for(int oid=1; ; oid++){
        fscanf(file_ptr, "%c", &first);
        if(first == '='){
            break;
        }
        fmove(file_ptr, col_before);
        fscanf(file_ptr, "%s", result);
        if(strcmp(result, _value) == 0){
            return oid;
        }
        fmove(file_ptr, col_after+2);
    }
    fclose(file_ptr);
    return -1;
}


/**
 * @brief 在数据库中更新一个数据
 * @param _db 数据库对象
 * @param _table 表名
 * @param _column 列名
 * @param _oid 行号
 * @param value 值
*/
void db_update(db* _db, const str _table, const str _column, const int _oid, const str value){
    if(map_get(&(_db->_master), _table) == 0){
        return;
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb+",);
    _table_skip_to_table(file_ptr, _table);
    table_info info = table_get_info(file_ptr);
    _table_word_check(file_ptr, info, _column);
    if(col_position == -1){
        return;
    }
    _table_word_local(file_ptr, info, _column);
    fseek(file_ptr, info.head, SEEK_SET);
    _table_skip_to_position(file_ptr, col_position, _oid);
    char format[16];
    sprintf(format, "%%%ds", col_local);
    fprintf(file_ptr, format, value);
    fclose(file_ptr);
}


/**
 * @brief 在数据库中更新一行数据
 * @param _db 数据库对象
 * @param _table 表名
 * @param _oid 行号
 * @param _values 值
*/
void db_update_lin(db* _db, const str _table, const int _oid, list _values){
    if(map_get(&(_db->_master), _table) == 0){
        return;
    }
    _file_safe_open(file_ptr, _db->_file_name, "rb+",);
    _table_skip_to_table(file_ptr, _table);
    table_info info = table_get_info(file_ptr);
    fseek(file_ptr, info.start, SEEK_SET);
    fmove(file_ptr, info.lin_width+2);
    char format[256] = {}, result[65536] = {};
    int result_len = 0, each_width = 0;
    for(int i=0; i<info.col_count; i++){
        fscanf(file_ptr, "%d", &each_width);
        sprintf(format, "%%%ds", each_width);
        sprintf(result + result_len, format, list_get(str, &_values, i));
        result_len += each_width;
    } 
    fseek(file_ptr, info.head, SEEK_SET);
    _table_skip_to_position(file_ptr, 1, _oid); 
    fprintf(file_ptr, "%s", result);
    fclose(file_ptr);
}


/**
 * @brief 压缩数据库
 * @param _db 数据库对象
*/
void db_vacuum(db* _db){
    char new_file_name[256 + 8];
    sprintf(new_file_name, "%s.vac", _db->_file_name);
    FILE* fin = fopen(_db->_file_name, "rb");
    FILE* fout = fopen(new_file_name, "wb");
    list tables = list_create(int);
    fseek(fin, 0, SEEK_END);
    int file_end = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    while(ftell(fin) < file_end){
        list_append(&tables, ftell(fin));
        _table_skip_to_next(fin);
    };
    char line[65536];
    for(int i=0; i<tables.length; i++ ){
        fseek(fin, list_get(int, &tables, i), SEEK_SET);
        table_info info = table_get_info(fin);
        if(map_get(&(_db->_master), info.table_name) == 0){
            continue;
        }
        while(1){
            fgets(line, 65536, fin);
            if(line[0] == '='){
                fprintf(fout, "======\r\n");
                break;
            }
            int is_empty_line = 1;
            for(int i=0; i<info.lin_width && line[i]; i++){
                if(line[i] != ' '){
                    is_empty_line = 0;
                    break;
                }
            }
            if(!is_empty_line){
                fprintf(fout, "%s", line);
            }
        }
    }
    list_free(&tables);
    fclose(fin);
    fclose(fout);
    remove(_db->_file_name);
    rename(new_file_name, _db->_file_name);
}


/**
 * @brief 关闭数据库
 * @param _db 数据库对象
*/
void db_close(db* _db){
    map_free(&(_db->_master));
}

/**
 * @brief 跳转到下一个表
 * @param _fp 文件指针
 * @return 下一个表的起始位置
*/
static int _table_skip_to_next(FILE* _fp){
    table_info info = table_get_info(_fp);
    fseek(_fp, info.start, SEEK_SET);
    char first_char=' ';
    while(!feof(_fp)){
        first_char = fgetc(_fp);
        if(first_char == '='){
            fmove(_fp, 7);
            break;
        }
        fmove(_fp, info.lin_width+1);
    }
    return ftell(_fp);
}


/**
 * @brief 跳转到指定的表
 * @param _fp 文件指针
 * @param _table 表名
 * @return 指定的表的起始位置
*/
static int _table_skip_to_table(FILE* _fp, const str _table){
    char table_name[256];
    int cursor = 0;
    fseek(_fp, 0, SEEK_SET);
    while(!feof(_fp)){
        fscanf(_fp, "%s", table_name);
        fseek(_fp, cursor, SEEK_SET);
        if(strcmp(table_name, _table) == 0){
            return cursor;
        }
        cursor = _table_skip_to_next(_fp);
    }
    return -1;
}


/**
 * @brief 跳转到指定的位置
 * @param _fp 文件指针
 * @param _column 列号
 * @param _oid 行号
 * @return 指定的位置
*/
static int _table_skip_to_position(FILE* _fp, const int _column, const int _oid){
    int lin_skip = 0, temp_int = 0;
    table_info info = table_get_info(_fp);
    fseek(_fp, info.start, SEEK_SET);
    fmove(_fp,2 + info.lin_width + 2);
    for(int i=1; i<_column; i++){
        fscanf(_fp, "%d", &temp_int);
        lin_skip += temp_int;
    }
    fseek(_fp, info.start, SEEK_SET);
    fmove(_fp, (info.lin_width+2)*2);
    fmove(_fp, (info.lin_width+2)*(_oid-1));
    fmove(_fp, lin_skip);
    return ftell(_fp);
}
