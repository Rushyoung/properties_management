//
// Created by Administrator on 2024/4/14.
//

#include <gtk/gtk.h>
#include <windows.h>
#include "../include/ui.h"
#include "../include/auth.h"

void change_window1(GtkWidget *widget, gpointer widget1){
    GtkWidget *window = widget1;
    gtk_widget_destroy(window);
    admin_work(0,NULL);
}

void change_window2(GtkWidget *widget, gpointer widget1){
    GtkWidget *window = widget1;
    gtk_widget_destroy(window);
    admin_resident(0,NULL);
}

void change_window3(GtkWidget *widget, gpointer widget1){
    GtkWidget *window = widget1;
    gtk_widget_destroy(window);
    admin_fee(0,NULL);
}

int data_backup(GtkWidget* widget, gpointer data){
    int a = database_backup(&database);
    MessageBox(
                NULL,
                TEXT("The data has backup in root directory as restore.db"),  // 显示的文本
                TEXT("NOTICE"),                // 标题
                MB_OK | MB_ICONERROR           // 风格：仅“确定”按钮和信息图标
    );
}

int data_recovery(GtkWidget* widget, gpointer data){
    int a = database_restore(&database);
    if(a == -1){
        MessageBox(
                NULL,
                TEXT("Can't find the file."
                     "Please place the file in your root directory!"),  // 显示的文本
                TEXT("WARNING!"),                // 标题
                MB_OK | MB_ICONERROR           // 风格：仅“确定”按钮和信息图标
        );
    }
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

    GtkWidget *worker_item = gtk_menu_item_new_with_label("工人管理");
    g_signal_connect(worker_item, "activate", G_CALLBACK(change_window1), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), worker_item);
    GtkWidget *fee_item = gtk_menu_item_new_with_label("费用管理");
    g_signal_connect(fee_item, "activate", G_CALLBACK(change_window3), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), fee_item);

    GtkWidget *resident_item = gtk_menu_item_new_with_label("居民管理");
    g_signal_connect(resident_item, "activate", G_CALLBACK(change_window2), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), resident_item);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_menu_item);

    gtk_table_attach(GTK_TABLE(table), menubar, 8, 9, 1, 2,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND, 3, 3);

    GtkWidget *button2 = gtk_button_new_with_label("数据备份");
    g_signal_connect(button2, "clicked", G_CALLBACK(data_backup), NULL);
    gtk_table_attach(GTK_TABLE(table), button2, 8, 9, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button1 = gtk_button_new_with_label("数据恢复");
    g_signal_connect(button1, "clicked", G_CALLBACK(data_recovery), NULL);
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
    g_signal_connect(button, "clicked", G_CALLBACK(password_page), NULL);
    gtk_table_attach(GTK_TABLE(table), button, 1, 2, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button), GTK_JUSTIFY_LEFT);

    GtkWidget *button3 = gtk_button_new_with_label("返回上一级");
    g_signal_connect(button3, "clicked", G_CALLBACK(change_page), window);
    gtk_table_attach(GTK_TABLE(table), button3, 1, 2, 7, 8,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

void page_change(GtkWidget *widget, gpointer data){
    GtkWidget *window = data;
    gtk_widget_destroy(window);
    admin_main(0,NULL);
}




typedef struct{
    GtkWidget *widget1;
    GtkWidget *widget2;
    GtkWidget *widget3;
    GtkWidget *widget4;
    GtkWidget *widget5;
    const char* username;
    const char* password;
    const char* name;
    const char* region;
    const char* time;
}worker_data;

void get_cleaner_data(GtkWidget* widget, gpointer data){
    worker_data *da = (worker_data *) data;
    da->username = gtk_entry_get_text(GTK_ENTRY(da->widget1));
    da->password = gtk_entry_get_text(GTK_ENTRY(da->widget2));
    da->name = gtk_entry_get_text(GTK_ENTRY(da->widget3));
    da->region = gtk_entry_get_text(GTK_ENTRY(da->widget4));
    da->time = gtk_entry_get_text(GTK_ENTRY(da->widget5));
    add_cleaner(&database, da->username, da->password, da->name, da->region, da->time);
}

void get_guard_data(GtkWidget* widget, gpointer data){
    worker_data *da = (worker_data *) data;
    da->username = gtk_entry_get_text(GTK_ENTRY(da->widget1));
    da->password = gtk_entry_get_text(GTK_ENTRY(da->widget2));
    da->name = gtk_entry_get_text(GTK_ENTRY(da->widget3));
    da->region = gtk_entry_get_text(GTK_ENTRY(da->widget4));
    da->time = gtk_entry_get_text(GTK_ENTRY(da->widget5));
    add_guard(&database, da->username, da->password, da->name, da->region, da->time);
}

int get_cleaner(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    worker_data da;
    worker_data *data = &da;

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 60, 40);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *table = gtk_table_new(6, 6, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *lable1 = gtk_label_new("用户名：");
    gtk_table_attach(GTK_TABLE(table), lable1, 0, 1, 0, 1,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable1), GTK_JUSTIFY_LEFT);

    GtkWidget *lable2 = gtk_label_new("密码：");
    gtk_table_attach(GTK_TABLE(table), lable2, 0, 1, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable2), GTK_JUSTIFY_LEFT);

    GtkWidget *label3 = gtk_label_new(" 姓名：");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label3), GTK_JUSTIFY_LEFT);

    GtkWidget *lable4 = gtk_label_new("区域：");
    gtk_table_attach(GTK_TABLE(table), lable4, 0, 1, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable4), GTK_JUSTIFY_LEFT);

    GtkWidget *lable5 = gtk_label_new("工作时间：");
    gtk_table_attach(GTK_TABLE(table), lable5, 0, 1, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *lable6 = gtk_label_new("示例输入（早九至晚九）：09002100");
    gtk_table_attach(GTK_TABLE(table), lable6, 1, 2, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 16);

    data->widget1 = entry1;

    GtkWidget *entry2 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 16);

    data->widget2 = entry2;

    GtkWidget *entry3 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry3), 10);

    data->widget3 = entry3;

    GtkWidget *entry4 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry4), 10);

    data->widget4 = entry4;

    GtkWidget *entry5 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry5, 1, 2, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry5), 10);

    data->widget5 = entry5;

    GtkWidget *button1 = gtk_button_new_with_label("确定");
    g_signal_connect(button1, "clicked", G_CALLBACK(get_cleaner_data), data);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button1), GTK_JUSTIFY_LEFT);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

int get_guard(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    worker_data da;
    worker_data *data = &da;

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 60, 40);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *table = gtk_table_new(6, 6, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *lable1 = gtk_label_new("用户名：");
    gtk_table_attach(GTK_TABLE(table), lable1, 0, 1, 0, 1,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable1), GTK_JUSTIFY_LEFT);

    GtkWidget *lable2 = gtk_label_new("密码：");
    gtk_table_attach(GTK_TABLE(table), lable2, 0, 1, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable2), GTK_JUSTIFY_LEFT);

    GtkWidget *label3 = gtk_label_new(" 姓名：");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label3), GTK_JUSTIFY_LEFT);

    GtkWidget *lable4 = gtk_label_new("区域：");
    gtk_table_attach(GTK_TABLE(table), lable4, 0, 1, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable4), GTK_JUSTIFY_LEFT);

    GtkWidget *lable5 = gtk_label_new("工作时间：");
    gtk_table_attach(GTK_TABLE(table), lable5, 0, 1, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *lable6 = gtk_label_new("示例输入（早九至晚九）：09:00-21:00");
    gtk_table_attach(GTK_TABLE(table), lable6, 4, 6, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 16);

    data->widget1 = entry1;

    GtkWidget *entry2 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 16);

    data->widget2 = entry2;

    GtkWidget *entry3 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry3), 10);

    data->widget3 = entry3;

    GtkWidget *entry4 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry4), 10);

    data->widget4 = entry4;

    GtkWidget *entry5 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry5, 1, 2, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry5), 16);

    data->widget5 = entry5;

    GtkWidget *button1 = gtk_button_new_with_label("确定");
    g_signal_connect(button1, "clicked", G_CALLBACK(get_guard_data), data);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button1), GTK_JUSTIFY_LEFT);

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


    GtkWidget *menubar2 = gtk_menu_bar_new();
    gtk_container_add(GTK_CONTAINER(window), menubar2);

    GtkWidget *file_menu_item2 = gtk_menu_item_new_with_label("录入工人信息");
    GtkWidget *file_menu2 = gtk_menu_new();

    GtkWidget *auth2_item = gtk_menu_item_new_with_label("保安");
    g_signal_connect(auth2_item, "activate", G_CALLBACK(get_guard), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu2), auth2_item);

    GtkWidget *auth3_item = gtk_menu_item_new_with_label("保洁");
    g_signal_connect(auth3_item, "activate", G_CALLBACK(get_cleaner), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu2), auth3_item);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item2), file_menu2);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar2), file_menu_item2);

    gtk_table_attach(GTK_TABLE(table), menubar2, 2, 3, 4, 5,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND, 3, 3);


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
    gtk_table_attach(GTK_TABLE(table), scoller, 5, 19, 5, 9,GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *lable = gtk_label_new("当前页面：管理员-工人管理");
    gtk_table_attach(GTK_TABLE(table), lable, 5, 19, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);

    GtkWidget *button = gtk_button_new_with_label("返回上一级");
    g_signal_connect(button, "clicked", G_CALLBACK(page_change), window);
    gtk_table_attach(GTK_TABLE(table), button, 15, 19, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

typedef struct{
    GtkWidget *widget1;
    GtkWidget *widget2;
    GtkWidget *widget3;
    GtkWidget *widget4;
    GtkWidget *widget5;
    const char* username;
    const char* password;
    const char* name;
    const char* region;
    const char* room;
}resident_data;

resident_data residentData;
resident_data *residentData_ptr = &residentData;

void get_resident_data(GtkWidget *widget, gpointer data){
    resident_data *temp = (resident_data *) data;
    temp->username = gtk_entry_get_text(GTK_ENTRY(temp->widget1));
    temp->password = gtk_entry_get_text(GTK_ENTRY(temp->widget2));
    temp->name = gtk_entry_get_text(GTK_ENTRY(temp->widget3));
    temp->region = gtk_entry_get_text(GTK_ENTRY(temp->widget4));
    temp->room = gtk_entry_get_text(GTK_ENTRY(temp->widget5));
    add_residents(&database, temp->username, temp->password, temp->name, temp->region, temp->room);
}

int get_resident(int argc, char *argv[]){
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

    GtkWidget *lable1 = gtk_label_new("用户名：");
    gtk_table_attach(GTK_TABLE(table), lable1, 0, 1, 0, 1,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable1), GTK_JUSTIFY_LEFT);

    GtkWidget *lable2 = gtk_label_new("密码：");
    gtk_table_attach(GTK_TABLE(table), lable2, 0, 1, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable2), GTK_JUSTIFY_LEFT);

    GtkWidget *label3 = gtk_label_new(" 姓名：");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label3), GTK_JUSTIFY_LEFT);

    GtkWidget *lable4 = gtk_label_new("楼栋：");
    gtk_table_attach(GTK_TABLE(table), lable4, 0, 1, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable4), GTK_JUSTIFY_LEFT);

    GtkWidget *lable5 = gtk_label_new("房间：");
    gtk_table_attach(GTK_TABLE(table), lable5, 0, 1, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable5), GTK_JUSTIFY_LEFT);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 20);

   residentData_ptr->widget1 = entry1;

    GtkWidget *entry2 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 20);

    residentData_ptr->widget2 = entry2;

    GtkWidget *entry3 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry3), 20);

    residentData_ptr->widget3 = entry3;

    GtkWidget *entry4 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry4), 20);

    residentData_ptr->widget4 = entry4;

    GtkWidget *entry5 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), entry5, 1, 2, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry5), 20);

    residentData_ptr->widget5 = entry5;

    GtkWidget *button1 = gtk_button_new_with_label("确定");
    g_signal_connect(button1, "clicked", G_CALLBACK(get_resident_data), residentData_ptr);
    gtk_table_attach(GTK_TABLE(table), button1, 2, 3, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button1), GTK_JUSTIFY_LEFT);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

int admin_resident(int argc, char *argv[]){
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

    GtkWidget *button1 = gtk_button_new_with_label("录入居民信息");
    g_signal_connect(button1, "clicked", G_CALLBACK(get_resident), NULL);
    gtk_table_attach(GTK_TABLE(table), button1, 2, 3, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button1), GTK_JUSTIFY_LEFT);

    GtkWidget *button2 = gtk_button_new_with_label("居民信息查询");
    g_signal_connect(button2, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button2, 2, 3, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button2), GTK_JUSTIFY_LEFT);

    GtkWidget *entry1 = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 10);
    gtk_entry_set_text(GTK_ENTRY(entry1), "姓名：");
    g_signal_connect(entry1, "activate", G_CALLBACK(entry_callback), entry1);
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button3 = gtk_button_new_with_label("居民信息删除");
    g_signal_connect(button3, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button3, 2, 3, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button3), GTK_JUSTIFY_LEFT);

    GtkWidget *entry2 = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry2), 16);
    gtk_entry_set_text(GTK_ENTRY(entry2), "用户名：");
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
    gtk_table_attach(GTK_TABLE(table), scoller, 5, 19, 5, 9,GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *lable = gtk_label_new("当前页面：管理员-居民管理");
    gtk_table_attach(GTK_TABLE(table), lable, 5, 19, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);

    GtkWidget *button = gtk_button_new_with_label("返回上一级");
    g_signal_connect(button, "clicked", G_CALLBACK(page_change), window);
    gtk_table_attach(GTK_TABLE(table), button, 15, 19, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

int admin_fee(int argc, char *argv[]){
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

    GtkWidget *lable = gtk_label_new("请设定收费金额：");
    gtk_table_attach(GTK_TABLE(table), lable, 2, 3, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 16);
    gtk_table_attach(GTK_TABLE(table), entry, 5, 7, 4, 5,
                     GTK_FILL|GTK_EXPAND, GTK_FILL|GTK_EXPAND, 0, 0);

    GtkWidget *button = gtk_button_new_with_label("确定");
    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button, 12, 17, 8, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button1 = gtk_button_new_with_label("返回上一级");
    g_signal_connect(button1, "clicked", G_CALLBACK(page_change), window);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 3, 8, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *lable1 = gtk_label_new("当前页面：管理员-收费管理");
    gtk_table_attach(GTK_TABLE(table), lable1, 10, 19, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable1), GTK_JUSTIFY_LEFT);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

