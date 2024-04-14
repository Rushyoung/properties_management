//
// Created by Administrator on 2024/4/14.
//

#include <gtk/gtk.h>

static void destroy_window_callback(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void entry_callback(GtkWidget *widget, gpointer entry)
{
    const gchar *entry_text;
    //获取文本内容
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    printf("entry content:%s\n", entry_text);
}

int _main(int argc, char *argv[]) {}

int login_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    /* 创建主窗口 */
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    /* 创建一个10x10的布局容器 */
    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    /*创建一个标签*/
    GtkWidget *label = gtk_label_new("");
    gtk_table_attach(GTK_TABLE(table), label, 9, 10, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_markup(GTK_LABEL(label),
                         "<span foreground='black'  font_desc='20'>欢迎使用世界树物业管理系统！</span>");

    GtkWidget *image = gtk_image_new_from_file("..\\logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 3, 0, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    /* 创建一个按钮 */
    GtkWidget *button = gtk_button_new_with_label("登录");
    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button, 8, 10, 8, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 5, 5);
    /* 创建两个文本框 */
    GtkWidget *username_entry1 = gtk_entry_new();
    g_signal_connect(username_entry1, "activate", G_CALLBACK(entry_callback), username_entry1);
    GtkWidget *password_entry1 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry1), FALSE);
    g_signal_connect(password_entry1, "activate", G_CALLBACK(entry_callback), password_entry1);

    GtkWidget *lable1 = gtk_label_new("用户名：");
    GtkWidget *lable2 = gtk_label_new("密码：");

    /* 将文本框添加到布局容器中 */
    gtk_table_attach(GTK_TABLE(table), username_entry1, 6, 14, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), password_entry1, 6, 14, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), lable1, 4, 6, 4, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), lable2, 4, 6, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);


    /* 显示所有窗口部件 */
    gtk_widget_show_all(window);
    /* 运行主循环 */
    gtk_main();

    return 0;
}


int admin_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    char i[5] = "yituo";

    /* 创建主窗口 */
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *image = gtk_image_new_from_file("E:\\cks\\logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 3, 0, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *label = gtk_label_new(i);
    gtk_table_attach(GTK_TABLE(table), label, 9, 10, 9, 8, GTK_FILL, GTK_FILL, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);

    GtkWidget *label1 = gtk_label_new("姓名：");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
