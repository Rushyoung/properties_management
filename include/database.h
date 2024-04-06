//
// Created by rushy on 2024/4/6.
//
#include "../include/base_type.h"
#include <stdio.h>


#ifndef PROPERTY_DATABASE_H

int fp_move(FILE*, long);

typedef struct{
    int head;
    int start;
    int column_count;
    int line_width;
    char table_name[256];
} table_info;





#define PROPERTY_DATABASE_H

#endif //PROPERTY_DATABASE_H
