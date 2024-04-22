//
// Created by rushy on 2024/4/6.
//
#include "../include/database.h"
#include <stdlib.h>

inline int fp_move(FILE* fp, long offset){
    if(offset < 0 || offset > 16){
        return fseek(fp, offset, SEEK_CUR);
    }
    for(long i = 0; i < offset; i++){
        fgetc(fp);
    }
    return 0;
}

int file_insert(FILE* fp, const char* data){
    long start = ftell(fp);
    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    char* buffer = (char*)malloc(sizeof(char) * (end - start + 2));
    if(buffer == NULL){
        return 1;
    }
    fseek(fp, start, SEEK_SET);
    fread(buffer, 1, end - start, fp);
    fseek(fp, start, SEEK_SET);
    fprintf(fp, "%s", data);
    fwrite(buffer, 1, end - start, fp);
    return 0;
}



table_info table_info_get(FILE* fp){
    table_info tb;
    tb.head = ftell(fp);
    fscanf(fp, "%s%d%d", tb.table_name, &tb.line_width, &tb.column_count);
    tb.start = ftell(fp) + 2;//TODO:transfer to long type
    fseek(fp, tb.head, SEEK_SET);
    return tb;
}

db database_connect(const char* _file_name){
    db _db;
    strcpy(_db.file_name, _file_name);
    _db.master = map_create();
    FILE* fp = fopen(_file_name, "rb");
    if(fp == NULL){
        fp = fopen(_file_name, "wb+");
        fprintf(fp, "master 24 2\r\n%16s%8s\r\n%16d%8d\r\n%16s%8d\r\n======\r\n",
        "table", "width", 16, 8, "master", 24);
        fclose(fp);
        map_set(&_db.master, "master", 24);
        return _db;
    }
    char table_name[256];
    int table_width = 0, file_cur = 65;
    while(1){
        fseek(fp, file_cur, SEEK_SET);
        char c = fgetc(fp);
        if(c == '=' || c == EOF){
            break;
        }
        fscanf(fp, "%s%d", table_name, &table_width);
        map_set(&(_db.master), table_name, table_width);
        file_cur += (24 + 2);
    }
    fclose(fp);
    return _db;
}

void database_insert_table(db* _db, str _table, map _column){
    if(map_get(&(_db->master), _table) != -1){
        return;
    }
    FILE* fp = fopen(_db->file_name, "rb+");
    if(fp == NULL){
        perror("insert_file_error");
    }
    int line_width = 0;
    int column_count = 0;
    for(int i = 0; i < _column.capacity; i++){
        if(_column.keys[i] != NULL) {
            column_count++;
            line_width += _column.values[i];
        }
    }
    skip_to_next_table(fp);
    fp_move(fp, -8);
    char format[256] = {};
    sprintf(format, "%16s%8d\r\n", _table, line_width);
    file_insert(fp, format);
    fclose(fp);
    fp = fopen(_db->file_name, "ab");
    fprintf(fp, "%s %d %d\r\n", _table, line_width, column_count);
    for(int i = 0; i < column_count; i++){
        sprintf(format, "%%%ds", _column.values[i]);
        fprintf(fp, format, _column.keys[i]);
    }
    fprintf(fp, "\r\n");
    for(int i = 0; i < column_count; i++){
        sprintf(format, "%%%dd", _column.values[i]);
        fprintf(fp, format, _column.values[i]);
    }
    fprintf(fp,"\r\n======\r\n");
    fclose(fp);
    map_set(&(_db->master), _table, line_width);
}


void database_insert_line(db* _db, str _table, list values){
    if(map_get(&(_db->master), _table) == -1){
        return;
    }
    FILE* fp = fopen(_db->file_name, "rb+");
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    fseek(fp, info.start + info.line_width + 2, SEEK_SET);
    char format[256] = {};
    char insert_data[65536] = {};
    int insert_len = 0, width = 0;
    for(int i = 0; i < info.column_count; i++){
        fscanf(fp, "%d", &width);
        sprintf(format, "%%%ds", width);
        printf("here: %s\n", *(char**)list_get_ptr(&values, i+1));
        sprintf(insert_data + insert_len, format, list_get(char*, &values, i+1));
        insert_len += width;
    }
    fseek(fp, info.head, SEEK_SET);
    skip_to_next_table(fp);
    fp_move(fp, -8);
    sprintf(insert_data + insert_len, "\r\n");
    file_insert(fp, insert_data);
    fclose(fp);
}

void database_remove_table(db* _db, str _table){
    if(map_get((&_db->master), _table) == -1){
        return;
    }
    map_remove(&_db->master, _table);
    FILE* fp = fopen(_db->file_name, "rb+");
    if(fp == NULL){
        perror("remove");
    }
    table_info info = table_info_get(fp);
    fseek(fp, info.start+info.line_width*2, SEEK_SET);
    char temp_char, temp_str[256];
    while(1){
        temp_char = fgetc(fp);
        if(temp_char == '='){
            break;
        }
        fscanf(fp, "%s", temp_str);
        if(strcmp(temp_str, _table) == 0){
            fp_move(fp, -16);
            fprintf(fp, "%24s", "");
            break;
        } else {
            fp_move(fp, 10);
        }
    }
    fclose(fp);
}


void database_remove_line(db* _db, str _table, int line_no){
    if(map_get(&_db->master, _table) == -1){
        return;
    }
    FILE* fp = fopen(_db->file_name, "rb+");
    if(fp == NULL){
        perror("remove");
    }
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    jump_to_position(fp, 1, line_no);
    char format[256] = {};
    sprintf(format, "%%%ds", info.line_width);
    fprintf(fp, format, "");
    fclose(fp);
}


int skip_to_next_table(FILE* _fp){
    table_info info = table_info_get(_fp);
    fseek(_fp, info.start, SEEK_SET);
    char first_char=' ';
    while(!feof(_fp)){
        first_char = fgetc(_fp);
        if(first_char == '='){
            fp_move(_fp, 7);
            break;
        }
        fp_move(_fp, info.line_width+1);
    }
    return ftell(_fp);
}


str database_select(db* _db, str _table, str _column, int line_no){
    if(map_get(&(_db->master), _table) == -1){
        return NULL;
    }
    FILE* fp = fopen(_db->file_name, "rb");
    if(fp == NULL){
        perror("select");
        return NULL;
    }
    int column_pos = -1;
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    fseek(fp, info.start, SEEK_SET);
    char column_name[256] = {};
    for(int i = 0; i < info.column_count; i++){
        fscanf(fp, "%s", column_name);
        if(strcmp(column_name, _column) == 0){
            column_pos = i;
        }
    }
    if(column_pos == -1) return NULL;
    fseek(fp, info.head, SEEK_SET);
    jump_to_position(fp, column_pos, line_no);
    char result[256];
    fscanf(fp, "%s", result);
    fclose(fp);
    return string(result);
}

list database_select_column(db* _db, str _table, str _column){
    if(map_get(&(_db->master), _table) == -1){
        return list_create(sizeof(void));
    }
    FILE* fp = fopen(_db->file_name, "rb");
    if(fp == NULL){
        perror("select");
        return list_create(sizeof(void));
    }
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    fseek(fp, info.start, SEEK_SET);
    int skip_width = 0, column_pos = -1;
    char column_name[256] = {};
    for(int i = 0; i < info.column_count; i++){
        fscanf(fp, "%s", column_name);
        if(strcmp(_column, column_name) == 0){
            column_pos = i;
        }
    }
    if(column_pos == -1){
        return list_create(sizeof(void));
    }
    for(int i = 0; i < column_pos; i++){
        int temp;
        fscanf(fp, "%d", &temp);
        skip_width += temp;
    }
    char temp[256] = {};
    char c;
    list result = list_create(sizeof(str));
    for(int line_no = 0;; line_no++){
        fseek(fp, info.start, SEEK_SET);
        fp_move(fp, (info.line_width + 2) * (line_no + 2));
        if((c = fgetc(fp)) == '=') break;
        fp_move(fp, skip_width);
        fscanf(fp, "%s", temp);
        str temp_ptr = string(temp);
        list_append(&result, &temp_ptr);
    }
    fclose(fp);
    return result;
}

dict database_select_line(db* _db, str _table, int line_no){
    if(map_get(&(_db->master), _table) == -1){
        perror("unknown table");
        return dict_create();
    }
    FILE* fp = fopen(_db->file_name, "rb");
    if(fp == NULL){
        perror("select");
        return dict_create();
    }
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    dict result = dict_create();
    fseek(fp, info.start, SEEK_SET);
    char temp[256];
    for(int i = 0; i < info.column_count; i++){
        fscanf(fp, "%s", temp);
        dict_set(&result, temp, "");
    }
    fseek(fp, info.start, SEEK_SET);
    fp_move(fp, (info.line_width + 2) * (line_no + 1));
    for(int i = 0; i < info.column_count; i++){
        fscanf(fp, "%s", temp);
        dict_set(&result, result.keys[i], temp);
    }
    fclose(fp);
    return result;
}

void database_update(db* _db, str _table, str _column, int line_no, str value){
    if(map_get(&(_db->master), _table) == -1){
        perror("no such table");
        return;
    }
    FILE* fp = fopen(_db->file_name, "rb+");
    if(fp == NULL){
        perror("update");
        return;
    }
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    int column_pos = -1;
    fseek(fp, info.start, SEEK_SET);
    char column_name[256] = {};
    for(int i = 0; i < info.column_count; i++){
        fscanf(fp, "%s", column_name);
        if(strcmp(column_name, _column) == 0){
            column_pos = i;
            
        }
    }
    if(column_pos == -1) return;
    int width = 0;
    for(int i = -1; i < column_pos; i++){
        fscanf(fp, "%d", &width);
    }
    fseek(fp, info.head, SEEK_SET);
    jump_to_position(fp, column_pos, line_no);
    char format[16] = {};
    sprintf(format, "%%%ds", width);
    fprintf(fp, format, value);
    fclose(fp);
}

void database_update_line(db* _db, str _table, int line_no, list _value){
    if(map_get(&(_db->master), _table) == -1){
        perror("no such table");
        return;
    }
    FILE* fp = fopen(_db->file_name, "rb");
    if(fp == NULL){
        perror("update");
        return;
    }
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    fseek(fp, info.start, SEEK_SET);
    fp_move(fp, info.line_width+2);
    char format[256] = {}, update[65536] = {};
    int update_len = 0, width = 0;
    for(int i = 0; i < info.column_count; i++){
        fscanf(fp, "%d", &width);
        sprintf(format, "%%%ds", width);
        sprintf(update + update_len, format, list_get_ptr(&_value, i));
        update_len += width;
    }
    fseek(fp, info.head, SEEK_SET);
    jump_to_position(fp, 1, line_no);
    fprintf(fp, "%s", update);
    fclose(fp);
}

void database_vacuum(db* _db){
    char new_filename[256+8] = {};
    sprintf(new_filename, "%s.vac", _db->file_name);
    FILE* input = fopen(_db->file_name, "rb");
    FILE* output = fopen(new_filename, "wb+");
    if(output == NULL) perror("create vacuum");
    list tables = list_create(sizeof(int));
    fseek(input, 0, SEEK_END);
    int file_end = ftell(input);
    fseek(input, 0, SEEK_SET);
    while(ftell(input) < file_end){
        long temp = ftell(input);
        list_append(&tables, &temp);
        skip_to_next_table(input);
    }
    char line[65536];
    for(int i = 0; i < tables.length; i++){
        int* _temp = (int*) list_get_ptr(&tables, i);
        fseek(input, *_temp, SEEK_SET);
        table_info info = table_info_get(input);
        if(map_get(&(_db->master), info.table_name) == -1){
            continue;
        }
        while(1){
            fgets(line, 65536, input);
            if(line[0] == '='){
                fprintf(output, "======\r\n");
                break;
            }
            int is_empty = 1;
            for(int j=0; j < info.line_width && line[j]; j++){
                if(line[j] != ' '){
                    is_empty = 0;
                    break;
                }
            }
            if(!is_empty){
                fprintf(output, "%s", line);
            }
        }
    }
    list_free(&tables);
    fclose(input);
    fclose(output);
    remove(_db->file_name);
    rename(new_filename, _db->file_name);
}



int jump_to_table(FILE* _fp, str _table){
    char table_name[256];
    int cursor = 0;
    fseek(_fp, 0, SEEK_SET);
    while(!feof(_fp)){
        fscanf(_fp, "%s", table_name);
        fseek(_fp, cursor, SEEK_SET);
        if(strcmp(table_name, _table) == 0){
            return cursor;
        }
        cursor = skip_to_next_table(_fp);
    }
    return -1;
}

int jump_to_position(FILE* fp, int column, int line){
    table_info info = table_info_get(fp);
    fseek(fp, info.start, SEEK_SET);
    fp_move(fp, 4 + info.line_width); //skip a line
    int temp, width_skip = 0;
    for(int i = 0; i < column; i++){
        fscanf(fp, "%d", &temp);
        width_skip += temp;
    }
    fseek(fp, info.start, SEEK_SET);
    fp_move(fp, (info.line_width + 2) * (line - 1 + 2) + width_skip);
    return ftell(fp);
}



db init(){
    db this = database_connect("data.db");
    if(this.master.keys[1] == NULL){
        //创建账号数据库
        map account = map_create();
        map_set(&account, "username", 16); // 16 is the max length of the
        map_set(&account, "password", 16); // username and password
        map_set(&account, "auth", 6); // auth token
        database_insert_table(&this, "account", account);
        map_free(&account);

        list admin = list_create(sizeof(char*));
        char* string1 = "admin";
        char* string2 = "000000";
        char* string3 = "0";
        list_append(&admin, &string1);
        list_append(&admin, &string2);
        list_append(&admin, &string3);
        database_insert_line(&this, "account", admin);
        list_free(&admin);

        map resident = map_create();
        map_set(&resident, "username", 16);
        map_set(&resident, "name", 10);
        map_set(&resident, "region", 10);
        map_set(&resident, "room", 8);
        map_set(&resident, "fee", 16);
        database_insert_table(&this, "resident", resident);
        map_free(&resident);

        map worker = map_create();
        map_set(&worker, "username", 16);
        map_set(&worker, "name", 10);
        map_set(&worker, "content", 16);
        map_set(&worker, "region", 10);
        database_insert_table(&this, "worker", worker);
        map_free(&worker);

        map bill = map_create();
        map_set(&bill, "ID", 16);
        map_set(&bill, "amount", 10);
        map_set(&bill, "time", 16);
        map_set(&bill, "username", 16);
        database_insert_table(&this, "bill", bill);
        map_free(&bill);
    }
    return this;
}

