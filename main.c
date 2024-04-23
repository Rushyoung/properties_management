#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "base_type.h"
#include "database.h"
#include "auth.h"

#include <gtk/gtk.h>

GtkBuilder *builder;
GObject *window;
char username[16], password[16];


void init_create_database();

void login();
void get_login_info();

int  get_user_auth(str);

void call_admin();
void call_worker();
void call_resident();

void init_create_database(){
    db goal = db_connect("data.db");

    map status = map_init( {"username", 16},
                           {"password", 16},
                           {"auth", 6} );
    db_insert_table(&goal, "status", status);
    map_free(&status);

    map user_info = map_init( {"username", 16},
                              {"phone", 16},
                              {"zone", 24} );
    db_insert_table(&goal, "user_info", user_info);
    map_free(&user_info);

    map fee = map_init( {"username", 16},
                        {"fee", 16},
                        {"paid", 16} );
    db_insert_table(&goal, "fee", fee);
    map_free(&fee);

    map log = map_init( {"username", 16},
                        {"time", 16},
                        {"action", 16},
                        {"amount", 16} );
    db_insert_table(&goal, "log", log);
    map_free(&log);

    list admin = list_init(string("admin"), string("ttakods"), string("0"));
    db_insert_lin(&goal, "status", admin);
    list_free(&admin);

    db_close(&goal);
}

int main() {
    gtk_init(NULL, NULL);
    // check if the database file do not exist
    if (access("data.db", F_OK) == -1){
        init_create_database();
    }
    login();
    int level = get_user_auth(username);
    switch(level){
        case 0:
            call_admin();
            break;
        case 1 ... 8:
            call_worker();
            break;
        case 9:
            call_resident();
            break;
        default:
            printf("Auth error\n");
            break;
    }
}

void login(){
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "assets/login.ui", NULL);
    window  = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GObject *login_button = gtk_builder_get_object(builder, "login_button");
    g_signal_connect(login_button, "clicked", G_CALLBACK(get_login_info), NULL);

    //show the window
    gtk_widget_show_all (GTK_WIDGET(window));

    gtk_main();
}

void get_login_info(){
    GObject *username_entry = gtk_builder_get_object(builder, "username_entry");
    GObject *password_entry = gtk_builder_get_object(builder, "password_entry");

    const gchar *username_text = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password_text = gtk_entry_get_text(GTK_ENTRY(password_entry));

    strcpy(username, username_text);
    strcpy(password, password_text);

    db data = db_connect("data.db");
    int oid = db_select_where(&data, "status", "username", username);

    if(oid == -1){
        printf("User not found\n");
        db_close(&data);
        return;
    }
    str auth = db_select(&data, "status", "password", oid);
    if(strcmp(auth, password) == 0){
        printf("Login success\n");
        //结束mainloop
        gtk_main_quit();
        builder = NULL;
        window = NULL;
    }else{
        printf("Password error\n");
    }
    db_close(&data);
}

int get_user_auth(str username){
    db data = db_connect("data.db");
    int oid = db_select_where(&data, "status", "username", username);
    str lvl = db_select(&data, "status", "auth", oid);
    int i_lvl = atoi(lvl);
    db_close(&data);
    return i_lvl;
}

void call_admin(){
    printf("Admin\n");
}

void call_worker(){
    printf("Worker\n");
}

void call_resident(){
    printf("Resident\n");
}