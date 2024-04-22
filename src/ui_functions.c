//
// Created by Administrator on 2024/4/21.
//


#include <stdio.h>
#include "../include/ui.h"





void destroy_window_callback(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void entry_callback(GtkWidget *widget, gpointer entry)
{
    const gchar *entry_text;
    //获取文本内容
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    printf("entry content:%s\n", entry_text);
}

void username_entry_callback(GtkWidget *widget, LoginData * data)
{
    const char *entry_text = gtk_entry_get_text(GTK_ENTRY(data->widget1));
    data->username = entry_text;
}

void password_entry_callback(GtkWidget *widget, LoginData * data){
    const char *entry_text = gtk_entry_get_text(GTK_ENTRY(data->widget2));
    data->password = entry_text;
}

void widget_destory(GtkWidget *widget, gpointer data){
    gtk_widget_destroy(widget);
}
