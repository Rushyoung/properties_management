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
#include "include/database.h"
#include "include/query.h"
#include "include/auth.h"


int main() {
    /*db the = init();*/
    str string3 = "username";
    str string1 = "admin";
    str string2 = "000000";
    printf("%s\n", database_query_by_column_to_column(&the, "account", "username", "admin", "password"));
    printf("%d", login_verify(&the, string1, string2));*/

    /*map user_info = map_create();
    map_set(&user_info, "username", 16);
    map_set(&user_info, "phone", 16);
    map_set(&user_info, "zone", 24);
    //向数据库中插入新表（table类型）（user_info）
    database_insert_table(&the, "user_info", user_info);
    map_free(&user_info);


    database_insert_line(&the, "user_info", admin);


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
    database_remove_table(&the, "log");
    database_vacuum(&the);

    database_update(&the, "user_info", "username", 1, "wss");
*/    return 0;
}
