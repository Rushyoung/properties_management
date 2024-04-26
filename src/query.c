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
    sort_struct* pairs = malloc(sizeof(sort_struct) * length);
    for(int i = 0, cur = 0; i < _data->capacity; i++){
        if(_data->keys[i] == NULL) continue;
        pairs[cur].key = _data->keys[i];
        pairs[cur].value = _data->values[i];
         cur++;
    }
    qsort(pairs, length, sizeof(sort_struct), qsort_compare);
    list result = list_create_by_size(int);
    for(int i = 0; i < length; i++){
        list_append(&result, &pairs[i].value);
    }
    return result;
}

list_link_head database_qsort(db* _database, str _table, str _column){
    list query = database_select_column(_database, _table, _column);
    map temp = map_create();
    for(int i = 1; i <= query.length; i++){
        map_set(&temp, list_get(char*, &query, i), i);
    }
    list line_no_result = qsort_by_map(&temp);
    if(map_get(&(_database->master), _table) == -1){
        perror("unknown table");
        return list_link_create();
    }
    FILE* fp = fopen(_database->file_name, "rb");
    if(fp == NULL){
        perror("select");
        return list_link_create();
    }
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    list_link_head head = list_link_create();
    for(int line_no = 0; line_no < line_no_result.length; line_no++){
        list result = list_create_by_size(char*);
        char temp_char[256];
        fseek(fp, info.start, SEEK_SET);
        fp_move(fp, (info.line_width + 2) * (*(int*)list_get_ptr(&line_no_result, line_no + 1) + 1));
        for (int i = 0; i < info.column_count; i++) {
            fscanf(fp, "%s", temp_char);
            str ttemp = string(temp_char);
            list_append(&result, &ttemp);
        }
        list_link_append(&head, result);
    }
    fclose(fp);
    return head;
}

list_link_head database_qsort_reverse(db* _database, str _table, str _column){
    list query = database_select_column(_database, _table, _column);
    map temp = map_create();
    for(int i = 1; i <= query.length; i++){
        map_set(&temp, list_get(char*, &query, i), i);
    }
    list line_no_result = qsort_by_map(&temp);
    if(map_get(&(_database->master), _table) == -1){
        perror("unknown table");
        return list_link_create();
    }
    FILE* fp = fopen(_database->file_name, "rb");
    if(fp == NULL){
        perror("select");
        return list_link_create();
    }
    jump_to_table(fp, _table);
    table_info info = table_info_get(fp);
    list_link_head head = list_link_create();
    for(int line_no = line_no_result.length-1; line_no >= 0; line_no--){
        list result = list_create_by_size(char*);
        char temp_char[256];
        fseek(fp, info.start, SEEK_SET);
        fp_move(fp, (info.line_width + 2) * (*(int*)list_get_ptr(&line_no_result, line_no + 1) + 1));
        for (int i = 0; i < info.column_count; i++) {
            fscanf(fp, "%s", temp_char);
            str ttemp = string(temp_char);
            list_append(&result, &ttemp);
        }
        list_link_append(&head, result);
    }
    fclose(fp);
    return head;
}

int qsort_compare(const void* a, const void* b){
    sort_struct* A = (sort_struct*)a;
    sort_struct* B = (sort_struct*)b;
    return strcmp(A->key, B->key);
}

list_link_head work_content_query(db* _database){
    FILE* fp = fopen(_database->file_name, "rb");
    jump_to_table(fp, "content");
    int line_count = count_line(fp);
    jump_to_table(fp, "content");
    table_info info = table_info_get(fp);
    list_link_head head = list_link_create();

    //?
    for(int line_no = 0; line_no < line_count; line_no++) {
        list result = list_create_by_size(char*);
        char temp_char[256];
        fseek(fp, info.start, SEEK_SET);
        fp_move(fp, (info.line_width + 2) * (line_no + 1));
        for (int i = 0; i < info.column_count; i++) {
            fscanf(fp, "%s", temp_char);
            str ttemp = string(temp_char);
            list_append(&result, &ttemp);
        }
        list_link_append(&head, result);
    }
    fclose(fp);
    return head;
}


list user_info_query(db* _database, str username){
    int auth = atoi(database_query_by_column_to_column(_database, "account", "username", username, "auth"));
    list result;
    switch (auth) {
        case 1:
            list overtime = check_pay(_database);
            if(overtime.length == 0){
                result = list_init(database_query_by_column_to_column(_database, "guard","username", username, "name"),
                                   database_query_by_column_to_column(_database, "guard","username", username, "region"),
                                   database_query_by_column_to_column(_database, "guard","username", username, "work_time"),
                                   "0");
                return result;
            }
            char over_time[10];
            sprintf(over_time, "%d", overtime.length);
            result = list_init(database_query_by_column_to_column(_database, "guard","username", username, "name"),
                                    database_query_by_column_to_column(_database, "guard","username", username, "region"),
                                    database_query_by_column_to_column(_database, "guard","username", username, "work_time"),
                                    over_time);
            return result;
        case 3:
            result = list_init(database_query_by_column_to_column(_database, "resident","username", username, "name"),
                                    database_query_by_column_to_column(_database, "resident","username", username, "region"),
                                    database_query_by_column_to_column(_database, "resident","username", username, "room"),
                                    database_query_by_column_to_column(_database, "resident","username", username, "fee"));
            return result;
    }
}


