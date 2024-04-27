//
// Created by Administrator on 2024/4/23.
//

#include <gtk/gtk.h>
#include <windows.h>
#include "../include/ui.h"

list name;

void get_personal_data(GtkWidget *widget, gpointer data){
    name = user_info_query(&database,passwordData.username);
}

void change_window(GtkWidget *widget, gpointer data){
    GtkWidget *window = data;
    gtk_widget_destroy(window);
    resident_main(0, NULL);
}

void resident_page_change1(GtkWidget *widget, gpointer data){
    GtkWidget *window = data;
    gtk_widget_destroy(window);
    resident_fee(0, NULL);
}


void resident_page_change2(GtkWidget *widget, gpointer data){
    GtkWidget *window = data;
    gtk_widget_destroy(window);
    resident_problem(0, NULL);
}

void resident_page_change3(GtkWidget *widget, gpointer data){
    GtkWidget *window = data;
    gtk_widget_destroy(window);
//    resident_inquire(0, NULL);
}

int resident_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    get_personal_data(NULL,NULL);
    //  创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *image = gtk_image_new_from_file("../logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 5, 0, 4,
                     GTK_FILL | GTK_EXPAND,GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *label = gtk_label_new("业主");
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);

    GtkWidget *label1 = gtk_label_new("姓名：");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_table_attach(GTK_TABLE(table), label1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *label2 = gtk_label_new(list_get(char*, &name, 1));
    gtk_table_attach(GTK_TABLE(table), label2, 2, 3, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_LEFT);

    GtkWidget *label3 = gtk_label_new("楼栋：");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_table_attach(GTK_TABLE(table), label3, 1, 2, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *label4 = gtk_label_new(list_get(char*, &name, 2));
    gtk_table_attach(GTK_TABLE(table), label4, 2, 3, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_LEFT);

    GtkWidget *label5 = gtk_label_new("房间：");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_table_attach(GTK_TABLE(table), label5, 1, 2, 7, 8,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *label6 = gtk_label_new(list_get(char*, &name, 3));
    gtk_table_attach(GTK_TABLE(table), label6, 2, 3, 7, 8,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_LEFT);

    GtkWidget *label7 = gtk_label_new("费用：");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_table_attach(GTK_TABLE(table), label7, 16, 17, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *label8 = gtk_label_new(list_get(char*, &name, 4));
    gtk_table_attach(GTK_TABLE(table), label8, 17, 18, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_LEFT);

    GtkWidget *button1 = gtk_button_new_with_label("修改密码");
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(password_change), NULL);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 8, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);


    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_container_add(GTK_CONTAINER(window), menubar);

    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("选择您要使用的功能——");
    GtkWidget *file_menu = gtk_menu_new();

    GtkWidget *fee_item = gtk_menu_item_new_with_label("费用缴纳");
    g_signal_connect(fee_item, "activate", G_CALLBACK(resident_page_change1), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), fee_item);

    GtkWidget *problem_item = gtk_menu_item_new_with_label("问题上报");
    g_signal_connect(problem_item, "activate", G_CALLBACK(resident_page_change2), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), problem_item);

    GtkWidget *inquire_item = gtk_menu_item_new_with_label("信息查询");
    g_signal_connect(inquire_item, "activate", G_CALLBACK(resident_page_change3), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), inquire_item);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_menu_item);
    gtk_table_attach(GTK_TABLE(table), menubar, 8, 9, 3, 4,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND, 3, 3);

    GtkWidget *lable = gtk_label_new("当前页面：业主界面");
    gtk_table_attach(GTK_TABLE(table), lable, 8, 9, 5, 7,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND, 3, 3);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

void generate_bill(GtkWidget* widget, gpointer data){
    pay(&database,passwordData.username);
    GtkWidget *window = (GtkWidget*)data;
    gtk_widget_destroy(window);
};

int fee_submit(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 60, 40);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *table = gtk_table_new(5, 5, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *label = gtk_label_new("收款码：");
    gtk_table_attach(GTK_TABLE(table), label, 0, 1, 0, 1,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);

    GtkWidget *image = gtk_image_new_from_file("../qrcode.png");
    gtk_table_attach(GTK_TABLE(table), image, 1, 4, 1, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(image), GTK_JUSTIFY_LEFT);

    GtkWidget *button1 = gtk_button_new_with_label("确定");
    g_signal_connect(button1, "clicked", G_CALLBACK(generate_bill), window);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button1), GTK_JUSTIFY_LEFT);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

int resident_fee(int argc, char *argv[]) {
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

    GtkWidget *image = gtk_image_new_from_file("../logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 5, 0, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *label = gtk_label_new("当前页面：用户界面-费用缴纳");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button1 = gtk_button_new_with_label("返回上一级");
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(change_window), window);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button2 = gtk_button_new_with_label("缴费");
    g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(fee_submit), NULL);
    gtk_table_attach(GTK_TABLE(table), button2, 4, 15, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button3 = gtk_button_new_with_label("缴费记录");
    g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(fee_submit), NULL);
    gtk_table_attach(GTK_TABLE(table), button3, 4, 15, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

void report_problem(GtkWidget* widget, gpointer data){
    GtkWidget *entry = (GtkWidget*)data;
    problem_report(&database, passwordData.username, gtk_entry_get_text(GTK_ENTRY(entry)));
}

int problem_submit(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 60, 40);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *table = gtk_table_new(4, 4, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *lable = gtk_label_new("故障描述");
    gtk_table_attach(GTK_TABLE(table), lable, 0, 1, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 32);
    gtk_table_attach(GTK_TABLE(table), entry, 1, 2, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry), 20);

    GtkWidget *button1 = gtk_button_new_with_label("确定");
    g_signal_connect(button1, "clicked", G_CALLBACK(report_problem), entry);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button1), GTK_JUSTIFY_LEFT);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
int resident_problem(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    //  创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *image = gtk_image_new_from_file("../logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 5, 0, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *label = gtk_label_new("当前页面：用户界面-问题上报");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button1 = gtk_button_new_with_label("返回上一级");
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(change_window), window);
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button2 = gtk_button_new_with_label("上报");
    g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(problem_submit), NULL);
    gtk_table_attach(GTK_TABLE(table), button2, 4, 15, 2, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *button3 = gtk_button_new_with_label("上报记录");
    g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(problem_submit), NULL);
    gtk_table_attach(GTK_TABLE(table), button3, 4, 15, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}



static GtkWidget *clist;
static gchar *title = {""};

void refill_clist_o() {

}

void on_worker_list_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Button clicked!\n");
    gtk_clist_clear(GTK_CLIST(user_data));
    refill_clist_o();
}

void on_fee_standard_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Button clicked!\n");
    gtk_clist_clear(GTK_CLIST(user_data));
    refill_clist_o();
}


int _main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    //  创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "用户查询");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);


    clist = gtk_clist_new_with_titles(2, title);
    gtk_table_attach_defaults(GTK_TABLE(table), clist, 2, 18, 2, 9);

    //调节4个title的相对位置
    gtk_clist_set_column_width(clist, 0, 260);
    gtk_clist_set_column_width(clist, 1, 260);


    // 创建第二个按钮
    GtkWidget *button2 = gtk_button_new_with_label("缴费历史查询");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_fee_standard_clicked), clist);
    gtk_table_attach(GTK_TABLE(table), button2, 11, 18, 1, 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);


    gtk_table_set_row_spacings(GTK_TABLE(table), 20);
    gtk_table_set_col_spacings(GTK_TABLE(table), 20);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
