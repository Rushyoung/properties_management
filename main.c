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
    update_password(&database, "mycomputerdad", "114514");
    list_link_head result = database_qsort(&database, "account", "username");
    struct list_link_node* cur = result.next;
    printf("%s\n", list_get(char*, &(cur->data), 1));
    cur = cur->next;
    printf("%s\n", list_get(char*, &(cur->data), 1));
    cur = cur->next;
    printf("%s\n", list_get(char*, &(cur->data), 1));
//    login_main(argc, argv);
    string1 = "manba";
    string2 = "000000";
    string3 = "kobe";
    string4 = "1d";
    string5 =  "101";
    add_residents(&database, string1, string2, string3, string4, string5);
    return 0;
}
