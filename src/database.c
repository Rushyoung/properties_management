#ifndef DEBUG
#include "database.h"
#endif

#include <stdio.h>
#include <string.h>


inline int fmove(FILE *_file, long _offset){
    if(_offset <= 0 || _offset > 16){
        return fseek(_file, _offset, SEEK_CUR);
    }
    for(long i=0; i<_offset; i++){
        int c = fgetc(_file);
        if (c == '\n') {
            i++;
        }
    }
    return 0;
}


db db_connect(const str _file_name){
    db _db;
    strcpy(_db._file_name, _file_name);
    _db._master = map_create();
    // read master
    FILE* file_ptr = fopen(_file_name, "r");
    if(file_ptr == NULL){
        return _db;
    }
    char table_name[256];
    int table_width;
    int file_cur = 65;
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


// insert 




// remove




// select
str db_select(db* _db, const str _table, const str _column, const int _oid){
    if(map_get(&(_db->_master), _table) == 0){
        return NULL;
    }
    FILE* file_ptr = fopen(_db->_file_name, "r");
    if(file_ptr == NULL){
        return NULL;
    }
    _table_skip_to_table(file_ptr, _table);
    char table_name[256];
    int lin_width = 0, col_count = 0;
    int col_position = -1;
    fscanf(file_ptr, "%s%d%d", table_name, &lin_width, &col_count);
    int table_start = ftell(file_ptr) + 2; // the endl is 2 bytes

    fseek(file_ptr, table_start, SEEK_SET);
    char column_name[256];
    for(int i = 0; i < col_count; i++){
        fscanf(file_ptr, "%s", column_name);
        if(strcmp(column_name, _column) == 0){
            col_position = i;
        }
    }
    if(col_position == -1){
        return NULL;
    }

    int lin_skip = 0;
    for(int i=0; i<col_position; i++){
        int temp_int;
        fscanf(file_ptr, "%d", &temp_int);
        lin_skip += temp_int;
    }

    fseek(file_ptr, table_start, SEEK_SET);
    fmove(file_ptr, (lin_width+2)*2);
    fmove(file_ptr, (lin_width+2)*(_oid-1));
    fmove(file_ptr, lin_skip);

    char result[256];
    fscanf(file_ptr, "%s", result);
    fclose(file_ptr);
    return string(result);
}


list db_select_col(db* _db, const str _table, const str _column){
    if(map_get(&(_db->_master), _table) == 0){
        return list_create(0);
    }
    FILE* file_ptr = fopen(_db->_file_name, "r");
    if(file_ptr == NULL){
        return list_create(0);
    }
    _table_skip_to_table(file_ptr, _table);
    char table_name[256];
    int lin_width = 0, col_count = 0;
    int col_position = -1;
    fscanf(file_ptr, "%s%d%d", table_name, &lin_width, &col_count);
    int table_start = ftell(file_ptr) + 2; // the endl is 2 bytes

    fseek(file_ptr, table_start, SEEK_SET);
    char column_name[256];
    for(int i = 0; i < col_count; i++){
        fscanf(file_ptr, "%s", column_name);
        if(strcmp(column_name, _column) == 0){
            col_position = i;
        }
    }
    if(col_position == -1){
        return list_create(0);
    }

    int lin_skip = 0;
    for(int i=0; i<col_position; i++){
        int temp_int;
        fscanf(file_ptr, "%d", &temp_int);
        lin_skip += temp_int;
    }
    char temp_char;
    list result = list_create(sizeof(str));
    for(int oid=0; ; oid++){
        fseek(file_ptr, table_start, SEEK_SET);
        fmove(file_ptr, (lin_width+2)*2);
        fmove(file_ptr, (lin_width+2)*oid);
        temp_char = fgetc(file_ptr);
        if(temp_char == '='){
            break;
        }
        fmove(file_ptr, lin_skip);
        char temp_str[256];
        fscanf(file_ptr, "%s", temp_str);
        str temp_str_ = string(temp_str);
        list_append(&result, &temp_str_);
    }
    fclose(file_ptr);
    return result;
}


dict db_select_lin(db* _db, const str _table, const int _oid){
    if(map_get(&(_db->_master), _table) == 0){
        return dict_create(0);
    }
    FILE* file_ptr = fopen(_db->_file_name, "r");
    if(file_ptr == NULL){
        return dict_create(0);
    }

    _table_skip_to_table(file_ptr, _table);
    char table_name[256];
    int lin_width = 0, col_count = 0;
    fscanf(file_ptr, "%s%d%d", table_name, &lin_width, &col_count);
    int table_start = ftell(file_ptr) + 2; // the endl is 2 bytes

    dict result = dict_create();
    fseek(file_ptr, table_start, SEEK_SET);
    char temp_str[256];
    for(int i=0; i<col_count; i++){
        fscanf(file_ptr, "%s", temp_str);
        dict_set(&result, temp_str, "");
    }

    fseek(file_ptr, table_start, SEEK_SET);
    fmove(file_ptr, (lin_width+2)*2);
    fmove(file_ptr, (lin_width+2)*(_oid-1));
    for(int i=0; i<col_count; i++){
        fscanf(file_ptr, "%s", temp_str);;
        dict_set(&result, result.keys[i], temp_str);
    }

    return result;
}


static int _table_skip_to_next(FILE* _fp){
    char table_name[256];
    int lin_width = 0, col_count = 0;
    fscanf(_fp, "%s%d%d", table_name, &lin_width, &col_count);
    fmove(_fp, 2);
    char first_char=' ';
    while(1 && !feof(_fp)){
        first_char = fgetc(_fp);
        if(first_char == '='){
            fmove(_fp, 7);
            break;
        }
        fmove(_fp, lin_width+1);
    }
    return ftell(_fp);
}


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
