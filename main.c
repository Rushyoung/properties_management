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
int main() {
    db new = database_connect("new.db");
    map newmap = map_create();
    map_set(&newmap, "newtable",16);
    map_set(&newmap, "what", 9);
    database_insert_table(&new, "test1", newmap);

    return 0;
}
