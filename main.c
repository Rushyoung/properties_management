/*
 * @Filename: main.c
 *
 * @Last editor: lzx
 *
 * @brief: main function file
 * @Create time: 2024/03/24
 *
 *
 */


#include <stdio.h>
#include "include/base_type.h"
#include "include/database.h"


int main() {
    db the = database_connect("data.txt");

    map status = map_create();
    map_set(&status, "username", 16); // 16 is the max length of the
    map_set(&status, "password", 16); // username and password
    map_set(&status, "auth", 6); // auth token

    database_insert_table(&the, "status", status);
    map_free(&status);

    map user_info = map_create();
    map_set(&user_info, "username", 16);
    map_set(&user_info, "phone", 16);
    map_set(&user_info, "zone", 24);
    //向数据库中插入新表（table类型）（user_info）
    database_insert_table(&the, "user_info", user_info);
    map_free(&user_info);
    list users = list_create(sizeof(char*));
    char* string1 = "what";
    char* string2 = "114514";
    char* string3 = "19d19h";
    list_append(&users, &string1);
    list_append(&users, &string2);
    list_append(&users, &string3);
    database_insert_line(&the, "user_info", users);
    list_free(&users);

    map fee = map_create();
    map_set(&fee, "username", 16);
    map_set(&fee, "fee", 16);
    map_set(&fee, "paid", 16);

    database_insert_table(&the, "fee", fee);
    map_free(&fee);

    map log = map_create();
    map_set(&log, "username", 16);
    map_set(&log, "time", 16);
    map_set(&log, "action", 16);
    map_set(&log, "amount", 16);

    database_insert_table(&the, "log", log);
    map_free(&log);
    str test = database_select(&the, "user_info", "phone", 1);
    printf("%s", database_select(&the, "user_info", "phone", 1));
    /*database_remove_table(&the, "log");*/
    /*database_vacuum(&the);*/
    return 0;
}
