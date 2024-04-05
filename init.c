#define DEBUG

#include "include/base_type.h"
#include "src/base_type.c"

#include "include/database.h"
#include "src/database.c"

#include <stdio.h>

int main(){
    db the = db_connect("data.db");

    map status = map_create();
    map_set(&status, "username", 16); // 16 is the max length of the 
    map_set(&status, "password", 16); // username and password
    map_set(&status, "auth", 6); // auth token

    db_insert_table(&the, "status", status);
    map_free(&status);

    map user_info = map_create();
    map_set(&user_info, "username", 16);
    map_set(&user_info, "phone", 16);
    map_set(&user_info, "zone", 24);

    db_insert_table(&the, "user_info", user_info);
    map_free(&user_info);

    map fee = map_create();
    map_set(&fee, "username", 16);
    map_set(&fee, "fee", 16);
    map_set(&fee, "paid", 16);

    db_insert_table(&the, "fee", fee);
    map_free(&fee);

    map log = map_create();
    map_set(&log, "username", 16);
    map_set(&log, "time", 16);
    map_set(&log, "action", 16);
    map_set(&log, "amount", 16);

    db_insert_table(&the, "log", log);
    map_free(&log);
}