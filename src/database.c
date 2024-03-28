#ifndef DEBUG
#include "database.h"
#endif

#include <stdio.h>
#include <string.h>

db db_create(){
    db _db;
    strcpy(_db._file_name, "");
    _db._master = map_create();
    return _db;
}


db db_open(const str _file_name){
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
    while(1){
        char table_name[256];
        fscanf(file_ptr, "%s", table_name);
        if(strcmp(table_name, _table) == 0){
            break;
        }
        char temp_char;
        do{
            temp_char = fgetc(file_ptr);
        }while(temp_char != '=');
        fseek(file_ptr, 7, SEEK_CUR);
    }
    int lin_width = 0;
    int col_count = 0;
    int col_position = -1;
    fscanf(file_ptr, "%d%d", &lin_width, &col_count);
    int table_start = ftell(file_ptr) + 2; // the endl is 2 bytes

    fseek(file_ptr, table_start, SEEK_SET);
    char column_name[256];
    for(int i = 0; i < col_count; i++){
        fscanf(file_ptr, "%s", column_name);
        if(strcmp(column_name, _column) == 0){
            col_position = i;
            break;
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
    fseek(file_ptr, (lin_width+2)*2, SEEK_CUR);
    fseek(file_ptr, (lin_width+2)*(_oid-1), SEEK_CUR);
    fseek(file_ptr, lin_skip, SEEK_CUR);

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
    char temp_char;
    while(1){
        char table_name[256];
        fscanf(file_ptr, "%s", table_name);
        if(strcmp(table_name, _table) == 0){
            break;
        }

        do{
            temp_char = fgetc(file_ptr);
        }while(temp_char != '=');
        fseek(file_ptr, 7, SEEK_CUR);
    }
    int lin_width = 0;
    int col_count = 0;
    int col_position = -1;
    fscanf(file_ptr, "%d%d", &lin_width, &col_count);
    int table_start = ftell(file_ptr) + 2; // the endl is 2 bytes

    fseek(file_ptr, table_start, SEEK_SET);
    char column_name[256];
    for(int i = 0; i < col_count; i++){
        fscanf(file_ptr, "%s", column_name);
        if(strcmp(column_name, _column) == 0){
            col_position = i;
            break;
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

    list result = list_create(sizeof(str));
    for(int oid=0; ;oid++){
        fseek(file_ptr, table_start, SEEK_SET);
        fseek(file_ptr, (lin_width+2)*2, SEEK_CUR);
        fseek(file_ptr, (lin_width+2)*oid, SEEK_CUR);
        temp_char = fgetc(file_ptr);
        if(temp_char == '='){
            break;
        }
        fseek(file_ptr, lin_skip - 1, SEEK_CUR);
        char temp_str[256];
        fscanf(file_ptr, "%s", temp_str);
        str temp_str_ = string(temp_str);
        list_append(&result, &temp_str_);
    }
    fclose(file_ptr);
    return result;
}