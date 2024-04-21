//
// Created by Administrator on 2024/4/20.
//
#include "../include/auth.h"
#ifndef PROPERTY_UI_H
#define PROPERTY_UI_H



typedef struct {
    int auth;
    int argc;
    char **argv;
    GtkWidget *window;
    GtkWidget *widget1;
    GtkWidget *widget2;
    const char* username;
    const char* password;
    db *the;
} LoginData;


int main(int argc, char *argv[]);
int admin_main(int argc, char *argv[]);
int scoller_main(int argc, char *argv[]);
int admin_work( int argc, char *argv[]);


void login_change(GtkWidget *widget, gpointer user_data);
void destroy_window_callback(GtkWidget *widget, gpointer data);
void username_entry_callback(GtkWidget *widget, LoginData * data);
void password_entry_callback(GtkWidget *widget, LoginData * data);
void entry_callback(GtkWidget *widget, gpointer entry);
void widget_destory(GtkWidget *widget, gpointer data);


#endif //PROPERTY_UI_H