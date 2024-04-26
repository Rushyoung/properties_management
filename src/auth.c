//
// Created by 小小喵姬 on 2024/4/20.
//
#include "../include/query.h"
#include "../include/ui.h"
#include <stdlib.h>
int login_verify(db* _database, str username, str password){
    int line_no = database_query_by_column(_database, "account", "username", username);
    perror("\n");
    if(line_no == -1) return -1;
    if(strcmp(password, database_select(_database, "account", "password", line_no)) == 0) {
        return atoi(database_select(_database, "account", "auth", line_no));
    }
    return -2;
}

int add_user(db* _database, str username, str password, str auth){
    str _auth = string(auth);
    if(database_query_by_column(_database, "account", "username", username) != -1){
        return -1;
    }
    list data = list_create(sizeof(char*));
    list_append(&data, &username);
    list_append(&data, &password);
    list_append(&data, &_auth);
    database_insert_line(_database, "account", data);
    list_free(&data);
    return 0;
}

/**
 * @return: user do not existed -1
 * */
int update_password(db* _database, str username, str new_password){
    int line_no = database_query_by_column(_database, "account", "username", username);
    if(line_no == -1) return -1;
    database_update(_database, "account", "password", line_no, new_password);
    return 0;
}

int add_guard(db* _database, str username, str password, str name, str region, str time){
    str auth = "1";
    if(add_user(_database, username, password, auth) == -1) return -1;
    list data = list_init(username, name, region, time);
    database_insert_line(_database, "guard", data);
    return 0;
}

int add_residents(db* _database, str username, str password, str name, str region, str room){
    str auth = "3";
    str fee = database_select(_database, "resident", "fee", 1);
    if(add_user(_database, username, password, auth) == -1) return -1;
    list data = list_init(username, name, region, room, fee, "0");
    database_insert_line(_database, "resident", data);
    return 0;
}

int add_cleaner(db* _database, str username, str password, str name, str region, str time){
    str auth = "2";
    if(add_user(_database, username, password, auth) == -1) return -1;
    list data = list_init(username, name, region, time);
    database_insert_line(_database, "guard", data);
    return 0;
}

void set_fee(db* _database, str fee){
    FILE* fp = fopen(_database->file_name, "rb+");
    jump_to_table(fp, "resident");
    int line_count = count_line(fp);
    for(int i = 1; i <= line_count; i++){
        database_update(_database, "resident", "fee", i, fee);
    }
    fclose(fp);
}




void problem_report(db* database, str username, str content){
    int line_no = database_query_by_column(database, "resident", "username", username);
    FILE* fp = fopen(database->file_name, "rb+");
    jump_to_table(fp, "content");
    int line_count = count_line(fp);
    str id;
    if(line_count == 0) id = "10000000";
    else{
        char format[10];
        sprintf(format, "%d", atoi(database_select(database, "content", "ID", line_count)) + 1);
        id = format;
    }
    list data = list_init(id, database_select(database, "resident", "region", line_no), database_select(database, "resident", "room", line_no), content, get_time());
    fclose(fp);
    database_insert_line(database, "content", data);
}

void problem_finish(db* _database, str id){
    int line_no = database_query_by_column(_database, "content", "ID", id);
    database_remove_line(_database, "content", line_no);
    database_vacuum(_database);
}

void pay(db* _database, str username){
    FILE* fp = fopen(_database->file_name, "rb+");
    jump_to_table(fp, "bill");
    int line_count = count_line(fp);
    str id;
    if(line_count == 0) id = "10000000";
    else{
        char format[10];
        sprintf(format, "%d", atoi(database_select(_database, "bill", "ID", line_count)) + 1);
        id = format;
    }
    list data = list_init(id,
                          database_query_by_column_to_column(_database, "resident", "username", username, "name"),
                          database_query_by_column_to_column(_database, "resident", "username", username, "region"),
                          database_query_by_column_to_column(_database, "resident", "username", username, "room"),
                          database_query_by_column_to_column(_database, "resident", "username", username, "fee"),
                          get_time(),
                          username);
    database_insert_line(_database, "bill", data);
    int line_no = database_query_by_column(_database, "resident", "username", username);
    database_update(_database, "resident", "last_time", line_no, get_time());
    fclose(fp);
}


list check_pay(db* _database){
    FILE* fp = fopen(_database->file_name, "rb");
    jump_to_table(fp, "resident");
    int line_count = count_line(fp);
    list result = list_create_by_size(int);
    for(int i = 1; i <= line_count; i++){
        //?
        if(check_time(database_select(_database, "resident", "last_time", i)) == 1){
            list_append(&result, &i);
        }
    }
    fclose(fp);
    return result;
}

list check_pay_user(db* _database, str username){
    FILE* fp = fopen(_database->file_name, "rb");
    jump_to_table(fp, "resident");
    int line_count = count_line(fp);
    list result = list_create_by_size(int);
    for(int i = 1; i <= line_count; i++){
        //?
        if(strcmp(username, database_select(_database, "account", "username", i)) == 0 && (check_time(database_select(_database, "resident", "last_time", i)) == 1)){
            list_append(&result, &i);
        }
    }
    fclose(fp);
    return result;
}


int delete_user(db* _database, str username){
    int auth = get_auth(_database, username);
    if(auth == -1) return -1;
    switch (auth) {
        case 1:
            database_remove_line(_database, "guard", database_query_by_column(_database, "guard", "username", username));
            database_remove_line(_database, "account", database_query_by_column(_database, "account", "username", username));
            database_vacuum(_database);
            return 0;
        case 3:
            database_remove_line(_database, "resident", database_query_by_column(_database, "resident", "username", username));
            database_remove_line(_database, "account", database_query_by_column(_database, "account", "username", username));
            return 0;
    }
    return -1;
}

inline int get_auth(db* _database, str username){
    if(database_query_by_column(_database, "account", "username", username) == -1) return -1;
    return atoi(database_query_by_column_to_column(_database, "account", "username", username, "auth"));
}


list_link_head check_pay_list(db* _database, str username){
    int auth = get_auth(_database, username);
    list query;
    switch (auth) {
        case 1:
            query = check_pay(_database);
            return database_select_line_list_link(_database, "resident", query);
        case 3:
    }
}