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
    return;
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    /* 创建主窗口 */
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    /* 创建一个10x10的布局容器 */
    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    /* 创建一个按钮 */
    GtkWidget *button = gtk_button_new_with_label("登录");
    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window_callback), NULL);

    /* 创建两个文本框 */
    GtkWidget *username_entry1 = gtk_entry_new();
    g_signal_connect(username_entry1, "activate", G_CALLBACK(entry_callback), username_entry1);

    GtkWidget *username_entry2 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(username_entry2), "用户名：");
    gtk_entry_set_editable(GTK_ENTRY(username_entry2), FALSE);

    GtkWidget *password_entry1 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry1), FALSE);
    g_signal_connect(password_entry1, "activate", G_CALLBACK(entry_callback), password_entry1);


    GtkWidget *password_entry2 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(password_entry2), "密码：");
    gtk_entry_set_editable(GTK_ENTRY(password_entry2), FALSE);

    /* 将文本框添加到布局容器中 */
    gtk_table_attach(GTK_TABLE(table), username_entry1, 5, 16, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), password_entry1, 5, 16, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), username_entry2, 4, 6, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), password_entry2, 4, 6, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_table_attach(GTK_TABLE(table), button, 6, 9, 7, 8,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND,5 , 5 );

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    /* 显示所有窗口部件 */
    gtk_widget_show_all(window);
    /* 运行主循环 */
    gtk_main();

    return 0;
}
