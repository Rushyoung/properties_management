//
// Created by rushy on 2024/4/6.
//
#include "../include/database.h"

inline int fp_move(FILE* fp, long offset){
    if(offset < 0 || offset > 16){
        return fseek(fp, offset, SEEK_CUR);
    }
    for(long i = 0; i < offset; i++){
        fgetc(fp);
    }
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
    FILE* fp = fopen(_file_name, "wb");
    if(fp == NULL){
        fp = fopen(_file_name, "wb+");
        fprintf(fp, "");
    }
}

