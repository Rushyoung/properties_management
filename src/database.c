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

int file_insert(FILE* fp, const str data){
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
}

db database_connect(const str _file_name){
    db _db;
    strcpy(_db.file_name, _file_name);
    _db.master = map_create();
    FILE* fp = fopen(_file_name, "wb");
    if(fp == NULL){
        fp = fopen(_file_name, "wb+");
        fprintf(fp, "master 24 2\r\n%16s%8s\r\n%16d%8d\r\n%16s%8d\r\n======\r\n",\
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

void database_insert(db _db, str _str, map _map){
    if(map_get(&_map, _str) != 0){
        return;
    }
    FILE* fp = fopen(_db.file_name, "rb");
    if(fp == NULL){
        perror("insert_file_error");
    }
    int line_count = 0;
    int column_width = 0;
    for(int i = 0; i < _map.capacity; i++){
        if(_map.keys[i] != NULL) {
            line_count++;
            if(strlen(_map.keys[i]) >= column_width){
                column_width = strlen(_map.keys[i]);
            }
        }

    }
    skip_to_next_table(fp);
}


void skip_to_next_table(FILE* fp){
    char c;
    while(1){
        c = fgetc(fp);
        if(c == EOF) return;
        if(c == '='){
            if((c= fgetc(fp)) == '\r'){
                if((c= fgetc(fp)) == '\n'){
                    return;
                }
            }
        }
    }
}