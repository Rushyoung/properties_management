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

#include "include/database.h"
#include "include/query.h"
#include "include/auth.h"
#include "include/ui.h"

db database;

int main(int argc, char *argv[]) {
    database = init();
    str string1 = "user1";
    str string2 = "1919810";
    str string3 = "liuhao";
    str string4 = "16";
    str string5 = "20230201";
    add_guard(&database, string1, string2, string3, string4, string5);
    string1 = "mycomputerdad";
    string2 = "000000";
    string3 = "mjc";
    string4 = "01";
    string5 = "19410614";
    add_guard(&database, string1, string2, string3, string4, string5);
    login_main(argc, argv);
    return 0;
}
