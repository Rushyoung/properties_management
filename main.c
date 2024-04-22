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
#include "include/ui.h"

db database;

int main(int argc, char *argv[]) {
    database = init();
    login_main(argc, argv);
    return 0;
}
