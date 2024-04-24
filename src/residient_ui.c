//
// Created by Administrator on 2024/4/23.
//

#include <gtk/gtk.h>
#include <windows.h>
#include "../include/ui.h"



int resident_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    //  创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *image = gtk_image_new_from_file("../asset/logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 5, 0, 4,
                     GTK_FILL | GTK_EXPAND,GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *label = gtk_label_new("业主");
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);

    GtkWidget *label1 = gtk_label_new("姓名：");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_table_attach(GTK_TABLE(table), label1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *label2 = gtk_label_new("白傻子");
    gtk_table_attach(GTK_TABLE(table), label2, 2, 3, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_LEFT);

    GtkWidget *button1 = gtk_button_new_with_label("修改密码");
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(password_change), NULL);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);


    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_container_add(GTK_CONTAINER(window), menubar);

    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("选择您要使用的功能——");
    GtkWidget *file_menu = gtk_menu_new();

    GtkWidget *fee_item = gtk_menu_item_new_with_label("费用缴纳");
    g_signal_connect(fee_item, "activate", G_CALLBACK(destroy_window_callback), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), fee_item);

    GtkWidget *problem_item = gtk_menu_item_new_with_label("问题上报");
    g_signal_connect(problem_item, "activate", G_CALLBACK(destroy_window_callback), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), problem_item);

    GtkWidget *inquire_item = gtk_menu_item_new_with_label("信息查询");
    g_signal_connect(inquire_item, "activate", G_CALLBACK(destroy_window_callback), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), inquire_item);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_menu_item);
    gtk_table_attach(GTK_TABLE(table), menubar, 8, 9, 1, 2,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND, 3, 3);

    GtkWidget *lable = gtk_label_new("当前页面：业主界面");
    gtk_table_attach(GTK_TABLE(table), lable, 8, 9, 0, 1,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND, 3, 3);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);

    GtkWidget *button = gtk_button_new_with_label("返回上一级");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(destroy_window_callback), window);
    gtk_table_attach(GTK_TABLE(table), button, 8, 9, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}