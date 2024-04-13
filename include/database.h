//
// Created by rushy on 2024/4/6.
//
#include "../include/base_type.h"
#include <stdio.h>
#include <string.h>

#ifndef PROPERTY_DATABASE_H

int fp_move(FILE*, long);
int file_insert(FILE*, const str);

typedef struct{
    int head;
    int start;
    int column_count;
    int line_width;
    char table_name[256];
} table_info;

table_info table_info_get(FILE*);



typedef struct{
    char file_name[256];
    map master;
} db;

db database_connect(const str);

void database_insert(db, str, map);

void skip_to_next_table(FILE*);

#define PROPERTY_DATABASE_H

#endif //PROPERTY_DATABASE_H
