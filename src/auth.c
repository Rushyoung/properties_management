//
// Created by 小小喵姬 on 2024/4/20.
//
#include "../include/query.h"
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
    str _username = string(username);
    str _password = string(password);
    str _auth = string(auth);
    if(database_query_by_column(_database, "account", "username", username) != -1){
        return -1;
    }
    list data = list_create(sizeof(char*));
    list_append(&data, &_username);
    list_append(&data, &_password);
    list_append(&data, &_auth);
    database_insert_line(_database, "account", data);
    list_free(&data);
    return 0;
}


int update_password(db* _database, str username, str new_password){
    int line_no = database_query_by_column(_database, "account", "username", username);
    if(line_no == -1) return -1;
    database_update(_database, "account", "password", line_no, new_password);
    return 0;
}