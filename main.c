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

//#define DEBUG

db database;

int main(int argc, char *argv[]) {
    database = init();
#ifdef DEBUG
    char username[20];
    char password[20];
    char name[20];
    char region[20];
    char room[20];
    char last_time[20];
    FILE* resident_fp = fopen("resident.txt", "rb");
    if(resident_fp != NULL){
        while(!feof(resident_fp)){
            fscanf(resident_fp, "%s %s %s %s %s %s", username, password, name,region, room, last_time);
            add_residents(&database, username, password, name, region, room);
            database_update(&database, "resident", "last_time", database_query_by_column(&database, "resident", "username", username), last_time);
        }
    }
    fclose(resident_fp);
    FILE* guard_fp = fopen("worker.txt", "rb");
    if(guard_fp != NULL){
        while (!feof(guard_fp)){
            fscanf(guard_fp, "%s %s %s %s %s", username, password, name, region, last_time);
            add_guard(&database, username, password, name, region, last_time);
        }
    }
    fclose(guard_fp);



#else
    login_main(argc, argv);




#endif

    return 0;
}
