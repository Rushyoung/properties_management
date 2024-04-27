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
//数据库横向映射查询接口
str database_query_by_column_to_column(db* _this, str _table, str src_column, str src_keyword, str dst_column);
list database_wide_query_to_line_No(db* _this, str _table, str _column, str keyword);
//模糊查询接口
list_link_head database_wide_query(db* _this, str _table, str _column, str keyword);


list qsort_by_map(map* _data);
//数据库排序接口
list_link_head database_qsort(db* _database, str _table, str _column);
//数据库倒序排序接口
list_link_head database_qsort_reverse(db* _database, str _table, str _column);
//保修问题查询接口
list_link_head work_content_query(db* _database);

list_link_head database_select_line_list_link(db* _database, str table, list query);
//用户个人信息查询接口
list user_info_query(db* _database, str username);

int qsort_compare(const void* a, const void* b);
#endif //PROPERTY_QUERY_H
