//
// Created by 小小喵姬 on 2024/4/20.
//

#include "../include/auth.h"

#ifndef PROPERTY_QUERY_H
#define PROPERTY_QUERY_H
typedef struct{
    str key;
    int value;
} sort_struct;


int database_query_by_column(db* _this, str _table, str _column, str _keyword);

str database_query_by_column_to_column(db* _this, str _table, str src_column, str src_keyword, str dst_column);

list database_wide_query_to_line_No(db* _this, str _table, str _column, str keyword);

list qsort_by_map(map* _data);
list database_qsort(db* _database, str _table, str _column);
list database_qsort_reverse(db* _database, str _table, str _column);

int qsort_compare(const void* a, const void* b);
#endif //PROPERTY_QUERY_H
