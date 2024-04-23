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


list database_wide_query_to_line_No(db* _this, str _table, str _column, str keyword){
    list final = list_create(sizeof(int));
    //test
    /*int tempnum = 0;*/
    int answer = database_query_by_column(_this, _table, _column, keyword);
    if(answer == -1){
        list result = database_select_column(_this, _table, _column);
        for(int i = 1; i <= result.length; i++){
            str temp = list_get(char*, &result, i);
            if(strstr(temp, keyword) != NULL){
                answer = i;
                list_append(&final, &i);
                //test
                /*tempnum++;
                printf("%d\n", list_get(int, &final, tempnum));*/
            }
        }
    }
    else{
        list result = database_select_column(_this, _table, _column);
        for (int i = 1; i <= result.length; i++) {
            str temp = list_get(char*, &result, i);
            if (strcmp(temp, keyword) == 0) {
                answer = i;
                list_append(&final, &i);
                //test
                /*tempnum++;
                printf("%d\n", list_get(int, &final, tempnum));*/
            }
        }
    }
    return final;
}
