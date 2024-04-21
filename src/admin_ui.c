//
// Created by Administrator on 2024/4/14.
//

#include <gtk/gtk.h>
#include <stdio.h>
#include <windows.h>
#include "../include/ui.h"

void change_window1(GtkWidget *widget, gpointer widget1){
    GtkWidget *window = widget1;
    int argc;
    char **argv;
    gtk_widget_destroy(window);
    admin_work(argc,argv);
}

//创建管理员页面
int admin_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    char *shuchu = "NULL";

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

    GtkWidget *label = gtk_label_new("管理员");
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);

    GtkWidget *label1 = gtk_label_new("姓名：");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_table_attach(GTK_TABLE(table), label1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *label2 = gtk_label_new("刘海柱");
    gtk_table_attach(GTK_TABLE(table), label2, 2, 3, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_container_add(GTK_CONTAINER(window), menubar);

    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("选择您要执行的任务——");
    GtkWidget *file_menu = gtk_menu_new();

    GtkWidget *open_item = gtk_menu_item_new_with_label("工人管理");
    g_signal_connect(open_item, "activate", G_CALLBACK(change_window1), window);


    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);

    GtkWidget *save_item = gtk_menu_item_new_with_label("费用管理");
    g_signal_connect(save_item, "activate", G_CALLBACK(destroy_window_callback), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);

    GtkWidget *exit_item = gtk_menu_item_new_with_label("居民管理");
    g_signal_connect(exit_item, "activate", G_CALLBACK(destroy_window_callback), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_item);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_menu_item);

    gtk_table_attach(GTK_TABLE(table), menubar, 8, 9, 1, 2,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND, 3, 3);

    GtkWidget *button2 = gtk_button_new_with_label("数据备份");
    g_signal_connect(button2, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button2, 8, 9, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button1 = gtk_button_new_with_label("数据恢复");
    g_signal_connect(button1, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button1, 8, 9, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    //创建一个带有滚动条的文本框
    GtkWidget *scoller = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scoller), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    //创建一个文本框
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);  // 设置自动换行

    //将文本框添加到滚动条中
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, shuchu, -1);

    //将文本视图添加到滚动窗格中
    gtk_container_add(GTK_CONTAINER(scoller), text_view);  // 将文本视图添加到滚动窗格中
    gtk_table_attach(GTK_TABLE(table), scoller, 5, 19, 5, 9,GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *button = gtk_button_new_with_label("密码维护");
    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button, 1, 2, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button), GTK_JUSTIFY_LEFT);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

int admin_work( int argc, char *argv[]){
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *image = gtk_image_new_from_file("../asset/logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 5, 0, 4,
                     GTK_FILL | GTK_EXPAND,GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *button1 = gtk_button_new_with_label("录入工人信息");
    g_signal_connect(button1, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button1, 2, 3, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button1), GTK_JUSTIFY_LEFT);

    GtkWidget *button2 = gtk_button_new_with_label("工人信息查询");
    g_signal_connect(button2, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button2, 2, 3, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button2), GTK_JUSTIFY_LEFT);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 20);
    gtk_entry_set_text(GTK_ENTRY(entry1), "");
    g_signal_connect(entry1, "activate", G_CALLBACK(entry_callback), entry1);
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button3 = gtk_button_new_with_label("工人信息删除");
    g_signal_connect(button3, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button3, 2, 3, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button3), GTK_JUSTIFY_LEFT);

    GtkWidget *entry2 = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 20);
    gtk_entry_set_text(GTK_ENTRY(entry2), "");
    g_signal_connect(entry2, "activate", G_CALLBACK(entry_callback), entry2);
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button3), GTK_JUSTIFY_LEFT);

    //创建一个带有滚动条的文本框
    GtkWidget *scoller = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scoller), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    //创建一个文本框
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);  // 设置自动换行

    //将文本框添加到滚动条中
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "wall leg shoot gun", -1);

    //将文本视图添加到滚动窗格中
    gtk_container_add(GTK_CONTAINER(scoller), text_view);  // 将文本视图添加到滚动窗格中
    gtk_table_attach(GTK_TABLE(table), scoller, 5, 19, 3, 9,GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);



    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
