//
// Created by 小小喵姬 on 2024/4/20.
//
#include "../include/query.h"

/*
 * @return NO. of line
 */
int database_query_by_column(db* _this, str _table, str _column, str _keyword){
    list result = database_select_column(_this, _table, _column);
    for(int i = 1; i <= result.length; i++){
        str temp = list_get(char*, &result, i);
        if(strcmp(_keyword, temp) == 0){
            return i;
        }
    }
    return -1;
}

str database_query_by_column_to_column(db* _this, str _table, str src_column, str src_keyword, str dst_column){
    int line_no = database_query_by_column(_this, _table, src_column, src_keyword);
    return string(database_select(_this, _table, dst_column, line_no));
}