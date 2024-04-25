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
    table_info info = table_info_get(fp);
    fseek(fp, info.start, SEEK_SET);
    fp_move(fp, (info.line_width+2) * 2);
    int line_count = 0;
    char c;
    while(1){
        fp_move(fp, info.line_width + 2);
        line_count++;
        if((c = fgetc(fp)) == '=') break;
        else{
            fp_move(fp, -1);
        }
    }
    for(int i = 1; i <= line_count; i++){
        database_update(_database, "resident", "fee", i, fee);
    }
}