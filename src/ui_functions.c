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

int password_change(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 60, 40);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *table = gtk_table_new(6, 5, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *label1 = gtk_label_new("请输入您的新密码:");
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
                     GTK_FILL|GTK_EXPAND, GTK_FILL|GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_LEFT);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 1, 2,
                     GTK_FILL|GTK_EXPAND, GTK_FILL|GTK_EXPAND, 0, 0);

    GtkWidget *button = gtk_button_new_with_label("修改密码");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(widget_destory), window);
    gtk_table_attach(GTK_TABLE(table), button, 1, 2, 3, 4,
                     GTK_FILL|GTK_EXPAND, GTK_FILL|GTK_EXPAND, 0, 0);


    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

void password_page(GtkWidget *widget, gpointer data)
{
    password_change(0, NULL);
}