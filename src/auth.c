//
// Created by 小小喵姬 on 2024/4/20.
//
#include "../include/query.h"
#include <stdlib.h>
int login_verify(db* _database, str username, str password){
    int line_no = database_query_by_column(_database, "account", "username", username);
    if(line_no == -1) return -1;
    if(strcmp(password, database_select(_database, "account", "password", line_no)) == 0) {
        return atoi(database_select(_database, "account", "auth", line_no));
    }
    return -2;
}

