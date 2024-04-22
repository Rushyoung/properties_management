//
// Created by Administrator on 2024/4/21.
//

#include <gtk/gtk.h>
#include <stdio.h>
#include <windows.h>
#include "../include/ui.h"
db database;

void login_analysis(GtkWidget *widget, LoginData *a){
    a->auth = login_verify(a->the,a->username,a->password);
}

void login_change(GtkWidget *widget, gpointer user_data) {
    LoginData *data = (LoginData *) user_data;
    int auth = data->auth;
    int argc = data->argc;
    char **argv = data->argv;
    GtkWidget *window = data->window;
    if(auth == -1){
        MessageBox(
                NULL,
                TEXT("The user is not existed."),  // 显示的文本
                TEXT("WARNING!"),                // 标题
                MB_OK | MB_ICONERROR           // 风格：仅“确定”按钮和信息图标
        );
    }
    if(auth == -2){
        MessageBox(
                NULL,
                TEXT("The password is incorrect."),  // 显示的文本
                TEXT("WARNING!"),                // 标题
                MB_OK | MB_ICONERROR           // 风格：仅“确定”按钮和信息图标
        );
    }
    if(auth == 0){
        gtk_widget_destroy(window);
        admin_main(argc,argv);
    }
    if(auth == 1){
        
    }
    if(auth == 2){

    }
    if(auth == 3){

    }
}

//创建登录页面
int login_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    //创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    LoginData a;
    database = init();
    a.the = &database;

    //创建一个10x10的布局容器

    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);


    //创建两个文本框


    GtkWidget *username_entry1 = gtk_entry_new();
    GtkWidget *password_entry1 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry1), FALSE);

    GtkWidget *lable1 = gtk_label_new("用户名：");
    GtkWidget *lable2 = gtk_label_new("密码：");

    //将文本框添加到布局容器中



    gtk_table_attach(GTK_TABLE(table), username_entry1, 6, 14, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), password_entry1, 6, 14, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), lable1, 4, 6, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), lable2, 4, 6, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

//创建一个标签

    GtkWidget *label = gtk_label_new("");
    gtk_table_attach(GTK_TABLE(table), label, 9, 10, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_markup(GTK_LABEL(label),"<span foreground='black'  font_desc='20'>欢迎使用世界树物业管理系统！</span>");

    GtkWidget *image = gtk_image_new_from_file("../asset/logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 3, 0, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    //创建一个按钮
    a.widget1 = username_entry1;
    a.widget2 = password_entry1;
    a.window = window;
    GtkWidget *button = gtk_button_new_with_label("登录");

    g_signal_connect(button, "clicked", G_CALLBACK(username_entry_callback), &a);
    g_signal_connect(button, "clicked", G_CALLBACK(password_entry_callback), &a);
    g_signal_connect(button, "clicked", G_CALLBACK(login_analysis), &a);
    gtk_table_attach(GTK_TABLE(table), button, 8, 10, 8, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND,5 , 5 );



    g_signal_connect(button, "clicked", G_CALLBACK(login_change), &a);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);


    //显示所有窗口部件

    gtk_widget_show_all(window);

    //运行主循环

    gtk_main();

    return 0;
}
