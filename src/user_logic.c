#include "user_logic.h"
#include "base_type.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <gtk/gtk.h>

extern GtkBuilder *builder;
extern GObject *window;

/* ==== admin logic ==== */
void admin_query_info(){
    printf("%s", __FUNCTION__);
}
void admin_statistic(){
    printf("%s", __FUNCTION__);
}

void admin_find_user(){
    printf("%s", __FUNCTION__);
}
void admin_add_user(){
    printf("%s", __FUNCTION__);
}
void admin_change_user(){
    printf("%s", __FUNCTION__);
}

void admin_del_user_password(){
    printf("%s", __FUNCTION__);
}

void admin_db_backup(){
    #ifdef _WIN32
    system("copy data.db data.db.bak");
    #else
    system("cp data.db data.db.bak");
    #endif
    GObject *text_view = gtk_builder_get_object(builder, "data_view");
    str show = "Database backup success!";
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)), show, -1);
}
void admin_db_restore(){
    #ifdef _WIN32
    system("copy data.db.bak data.db");
    #else
    system("cp data.db.bak data.db");
    #endif
}
void admin_db_view(){
    printf("%s", __FUNCTION__);
}