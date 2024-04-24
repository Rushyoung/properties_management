//
// Created by 小小喵姬 on 2024/4/20.
//
#include "../include/query.h"
#include <stdlib.h>
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


list qsort_by_map(map* _data){
    int length = 0;
    for(int i = 0; i < _data->capacity; i++){
        if(_data->keys[i] == NULL) continue;
        length++;
    }
    sort_struct* paris = malloc(sizeof(sort_struct) * length);
    for(int i = 0, cur = 0; i < _data->capacity; i++){
        if(_data->keys[i] == NULL) continue;
         paris[cur].key = _data->keys[i];
         paris[cur].value = _data->values[i];
         cur++;
    }
    qsort(paris, length, sizeof(sort_struct), qsort_compare);
    list result = list_create_by_size(int);
    for(int i = 0; i < length; i++){
        list_append(&result, &paris[i].value);
    }
    return result;
}


int qsort_compare(const void* a, const void* b){
    sort_struct* A = (sort_struct*)a;
    sort_struct* B = (sort_struct*)b;
    return strcmp(A->key, B->key);
}