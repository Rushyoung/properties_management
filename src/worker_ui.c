//
// Created by 小灰灰 on 24-4-23.
//


//#include "include/ui.h"
/*
#include "../include/database.h"
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
*/

//static void on_button3_clicked(GtkButton *button, gpointer user_data) {
//    gtk_widget_show_all(user_data);
//}

//int main(int argc, char *argv[]) {
//    gtk_init(&argc, &argv);
//    // 创建主窗口
//    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
//    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
//    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
//    // 创建一个10x10的布局容器
//    GtkWidget *table = gtk_table_new(10, 20, FALSE);
//    gtk_container_add(GTK_CONTAINER(window), table);
//
//    //创建一个标签
//    GtkWidget *label = gtk_label_new("");
//    gtk_table_attach(GTK_TABLE(table), label, 9, 10, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
//    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
//    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
//    gtk_label_set_markup(GTK_LABEL(label),"<span foreground='black'  font_desc='20'>欢迎使用世界树物业管理系统！</span>");
//
//
//    //创建一个按钮
//    GtkWidget *button = gtk_button_new_with_label("登录");
//    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window_callback), NULL);
//    gtk_table_attach(GTK_TABLE(table), button, 8, 10, 8, 9,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND,5 , 5 );
//    //创建两个文本框
//    GtkWidget *username_entry1 = gtk_entry_new();
//    g_signal_connect(username_entry1, "activate", G_CALLBACK(entry_callback), username_entry1);
//    GtkWidget *password_entry1 = gtk_entry_new();
//    gtk_entry_set_visibility(GTK_ENTRY(password_entry1), FALSE);
//    g_signal_connect(password_entry1, "activate", G_CALLBACK(entry_callback), password_entry1);
//
//    GtkWidget *lable1 = gtk_label_new("用户名：");
//    GtkWidget *lable2 = gtk_label_new("密码：");
//
//    //将文本框添加到布局容器中
//    gtk_table_attach(GTK_TABLE(table), username_entry1, 6, 14, 4, 5,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table), password_entry1, 6, 14, 6, 7,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table), lable1, 4, 6, 4, 5,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table), lable2, 4, 6, 6, 7,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//
//    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
//    gtk_table_set_col_spacings(GTK_TABLE(table), 30);
//
//
//    // 显示所有窗口部件
//    gtk_widget_show_all(window);
//    //运行主循环
//    gtk_main();
//
//    return 0;
//}

void widget_destory(GtkWidget *widget, gpointer data){
    gtk_widget_destroy(widget);
}


//保洁页面
//int main(int argc, char *argv[]){
//    gtk_init(&argc, &argv);
//    // 创建主窗口
//    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
//    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
//    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
//
//    // 创建一个10x10的布局容器
//    GtkWidget *table = gtk_table_new(10, 20, FALSE);
//    gtk_container_add(GTK_CONTAINER(window), table);
//
//    //创建6个标签
//    GtkWidget *label1_1 = gtk_label_new("用户信息");
//    GtkWidget *label1_2 = gtk_label_new("操作选项");
//    GtkWidget *label2_1 = gtk_label_new("姓名");
//    GtkWidget *label3_1 = gtk_label_new("工作区域");
//    GtkWidget *label2_2 = gtk_label_new("");
//    GtkWidget *label3_2 = gtk_label_new("");
//
//    //创建一个按钮
//    GtkWidget *button = gtk_button_new_with_label("密码维护");
//
//    //系统性定位
//    gtk_table_attach(GTK_TABLE(table), label1_1, 2, 11, 2, 4,
//                    GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table), label1_2, 10, 18, 2, 4,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table), label2_1, 2, 7, 4, 6,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table), label2_2, 6, 11, 4, 6,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table), label3_1, 2, 7, 6, 8,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table), label3_2, 6, 11, 6, 8,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//
//    gtk_table_attach(GTK_TABLE(table), button, 12, 17, 5, 7,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//
//    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
//    gtk_table_set_col_spacings(GTK_TABLE(table), 30);
//
//    // 显示所有窗口部件
//    gtk_widget_show_all(window);
//    //运行主循环
//    gtk_main();
//
//    return 0;
//}




////保安界面兼二级跳转
//void on_paytime_activated(GtkMenuItem *item, gpointer user_data) {
//    printf("按照缴费时间排序\n");
//    // 实现打开文件的操作...
//}
//
//void  on_building_activated(GtkMenuItem *item, gpointer user_data) {
//    printf("按照楼栋号排序\n");
//    //实现保存文件的操作...
//}
//
//void on_name_activated(GtkMenuItem *item, gpointer user_data) {
//    printf("按照名字排序\n");
//}
//
//void on_combobox_changed(GtkComboBox *combo, gpointer user_data) {
//    // 获取当前选中的文本
//    const gchar *selected_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo));
//
//    // 根据 selected_text 执行相应的排序操作
//    // ...
//}
//
//void close_window2_only(GtkWidget *window2) {
//    gtk_widget_destroy(window2);
//    window2=NULL;
//    gtk_main();
//}
//
//size_t i;
//gchar *resident_data[4];
//
//static GtkWidget *entry;
//static GtkWidget *clist;
//static gchar *title[4] = {"姓名", "楼栋号", "房间号", "缴费费用"};
//
//struct Resident {
//    char name[50];          // 姓名
//    int building_number;    // 楼栋号
//    int room_number;        // 房间号
//    double payment_amount;  // 缴费费用
//    // 可以添加其他字段，如最后一次缴费时间等
//};
//struct Resident residents[5]={
//        {"张三", 1, 101, 1000.0},
//        {"李四", 2, 201, 2000.0},
//        {"王五", 3, 301, 3000.0},
//        {"赵六", 4, 401, 4000.0},
//        {"孙七", 5, 501, 5000.0}
//};
//GtkWidget *window2 = NULL;
//static void generate_window2(void) {
//    //二级界面
//    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_window_set_title(GTK_WINDOW(window2), "世界树物业管理系统");
//    gtk_window_set_default_size(GTK_WINDOW(window2), 600, 400);
//    g_signal_connect(G_OBJECT(window2), "destroy", G_CALLBACK(close_window2_only), NULL);
//
//    gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);
//
//    // 创建一个16x10的布局容器
//    GtkWidget *table2 = gtk_table_new(10, 20, FALSE);
//    gtk_container_add(GTK_CONTAINER(window2), table2);
//
//
//    GtkWidget *label1 = gtk_label_new("姓名");
//    GtkWidget *label2 = gtk_label_new("楼栋号");
//    GtkWidget *label3 = gtk_label_new("房间号");
//    GtkWidget *label4 = gtk_label_new("缴费费用");
//
//    gtk_table_attach(GTK_TABLE(table2), label1, 2, 5, 3, 4,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table2), label2, 6, 9, 3, 4,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table2), label3, 10, 13, 3, 4,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table2), label4, 14, 17, 3, 4,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//
//
//    GtkWidget *menubar = gtk_menu_bar_new();
//    gtk_container_add(GTK_CONTAINER(window2), menubar);
//
//    // 创建“排列方式”菜单项及其子菜单项
//    GtkWidget *combo = gtk_combo_box_new_text();
//
//// 添加组合框项
//    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "按最后一次缴费时间");
//    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "按居住的楼栋号");
//    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "按姓名");
//
//// 连接“changed”信号处理程序，根据需要实现相应的排序逻辑
//    g_signal_connect(combo, "changed", G_CALLBACK(on_combobox_changed), NULL);
//
//// 将组合框添加到表格
//    gtk_table_attach_defaults(GTK_TABLE(table2), combo, 0, 6, 0, 1);
//
//// ... 创建输入框（entry）的代码不变
//
//// 将输入框添加到表格
//    gtk_table_attach_defaults(GTK_TABLE(table2), entry, 6, 14, 0, 1);
//
//
//
//    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("排列方式");
//    GtkWidget *file_menu = gtk_menu_new();
//
//    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), paytime_item);
//
//    GtkWidget *building_item = gtk_menu_item_new_with_label("按居住的楼栋号");
//    g_signal_connect(building_item, "activate", G_CALLBACK(on_building_activated), NULL);
//    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), building_item);
//
//    GtkWidget *name_item = gtk_menu_item_new_with_label("按姓名");
//    g_signal_connect(name_item, "activate", G_CALLBACK(on_name_activated), NULL);
//    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), name_item);
//
//    GtkWidget *paytime_item = gtk_menu_item_new_with_label("按最后一次缴费时间");
//    g_signal_connect(paytime_item, "activate", G_CALLBACK(on_paytime_activated), NULL);
//
//    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
//    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_menu_item);
//
//
//    //输入框
//    entry = gtk_entry_new();
//    gtk_table_attach_defaults(GTK_TABLE(table2), entry, 6, 14, 1, 3);
//
//
//    GtkWidget *button = gtk_button_new_with_label("搜索");
//    gtk_table_attach(GTK_TABLE(table2), button, 14, 17, 1, 3,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//
//
//    gtk_table_set_row_spacings(GTK_TABLE(table2), 30);
//    gtk_table_set_col_spacings(GTK_TABLE(table2), 30);
//
//
//
//    clist = gtk_clist_new_with_titles(4, title);
//    gtk_table_attach_defaults(GTK_TABLE(table2), clist, 2, 17, 4, 12);
//
//    //调节4个title的位置
//    gtk_clist_set_column_width(clist, 0, 80);
//    gtk_clist_set_column_width(clist, 1, 80);
//    gtk_clist_set_column_width(clist, 2, 80);
//    gtk_clist_set_column_width(clist, 3, 80);
//
//    //点击时清空列表，刷新居民信息
//    void on_search_clicked(GtkWidget *button, gpointer user_data);
//    g_signal_connect(button, "clicked", G_CALLBACK(on_search_clicked), clist);
//
//    gtk_widget_show_all(window2);
//
//}
//void (*generate_window2_ptr)(void) = generate_window2;
//void on_button3_clicked(GtkButton *button, gpointer *user_data) {
//    generate_window2();
//}
//
//
//
//static void generate_windows3(){
//    GtkWidget *window3=gtk_window_new(GTK_WINDOW_TOPLEVEL);
//
//}
//
//
//
//int main(int argc, char *argv[]) {
//    gtk_init(&argc, &argv);
//    // 创建主窗口
//    GtkWidget *window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_window_set_title(GTK_WINDOW(window1), "世界树物业管理系统");
//    gtk_window_set_default_size(GTK_WINDOW(window1), 600, 400);
//    g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//    gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
//
//    // 创建一个10x10的布局容器
//    GtkWidget *table1 = gtk_table_new(16, 20, FALSE);
//    gtk_container_add(GTK_CONTAINER(window1), table1);
//
//    //创建8个标签
//    GtkWidget *label1_1 = gtk_label_new("用户信息");
//    GtkWidget *label1_2 = gtk_label_new("操作选项");
//    GtkWidget *label2_1 = gtk_label_new("姓名");
//    GtkWidget *label3_1 = gtk_label_new("工作区域");
//    GtkWidget *label4_1 = gtk_label_new("工作时间");
//    GtkWidget *label5_1 = gtk_label_new("未缴费用户数量");
//    GtkWidget *label2_2 = gtk_label_new("");
//    GtkWidget *label3_2 = gtk_label_new("");
//    GtkWidget *label4_2 = gtk_label_new("");
//    GtkWidget *label5_2 = gtk_label_new("");
//
//    //创建3个按钮
//    GtkWidget *button1 = gtk_button_new_with_label("完成业主报修");
//    GtkWidget *button2 = gtk_button_new_with_label("密码维护");
//    GtkWidget *button3 = gtk_button_new_with_label("业主账单查询");
//
//    //系统定位
//    gtk_table_attach(GTK_TABLE(table1), label1_1, 2, 11, 2, 5,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label1_2, 10, 18, 2, 5,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label2_1, 2, 7, 5, 7,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label2_2, 6, 11, 5, 7,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label3_1, 2, 7, 7, 9,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label3_2, 6, 11, 7, 9,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label4_1, 2, 7, 9, 11,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label4_2, 6, 11, 9, 11,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label5_1, 2, 7, 11, 14,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), label5_2, 6, 11, 11, 14,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//
//
//    gtk_table_attach(GTK_TABLE(table1), button1, 12, 17, 5, 8,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), button2, 12, 17, 8, 11,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//    gtk_table_attach(GTK_TABLE(table1), button3, 12, 17, 11, 14,
//                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
//
//    gtk_table_set_row_spacings(GTK_TABLE(table1), 30);
//    gtk_table_set_col_spacings(GTK_TABLE(table1), 30);
//
//
//    GtkWidget *main_window = window1;
//    g_signal_connect(button3, "clicked", G_CALLBACK(on_button3_clicked), main_window);
//
//
//    // 显示所有窗口部件
//    gtk_widget_show_all(window1);
//    //运行主循环
//    gtk_main();
//
//
//}
//
//void refill_clist() {
//    for (i = 0; i < 5; ++i) {
//        resident_data[0] = g_strdup(residents[i].name);
//        resident_data[1] = g_strdup_printf("%d", residents[i].building_number);
//        resident_data[2] = g_strdup_printf("%d", residents[i].room_number);
//        resident_data[3] = g_strdup_printf("%.2f", residents[i].payment_amount);
//        gtk_clist_append(GTK_CLIST(clist), (gchar **) resident_data);
//    }
//}
//
//void on_search_clicked(GtkWidget *button, gpointer user_data) {
//    // 清空列表
//    gtk_clist_clear(GTK_CLIST(user_data));
//    refill_clist();
//}

/*

#include <string.h>

static GtkWidget *clist;
static gchar *title[2] = {"姓名", "楼栋号"};

size_t i;

struct Resident {
    char name[50];          // 姓名
    int building_number;    // 楼栋号
    int room_number;        // 房间号
    double payment_amount;  // 缴费费用
    // 可以添加其他字段，如最后一次缴费时间等
};
struct Resident residents[5]={
        {"张三", 1, 101, 1000.0},
        {"李四", 2, 201, 2000.0},
        {"王五", 3, 301, 3000.0},
        {"赵六", 4, 401, 4000.0},
        {"孙七", 5, 501, 5000.0}
};


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "未完成工作处理");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 创建一个16x20的布局容器
    GtkWidget *table = gtk_table_new(16, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    GtkWidget *entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(window), entry);
    gtk_table_attach_defaults(GTK_TABLE(table), entry, 6, 14, 1, 3);

    GtkWidget *button1 = gtk_button_new_with_label("返回");
    GtkWidget *button2 = gtk_button_new_with_label("删除");
    gtk_table_attach_defaults(GTK_TABLE(table), button1, 2, 6, 1, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), button2, 14, 18, 1, 3);


    clist = gtk_clist_new_with_titles(2, title);
    gtk_table_attach_defaults(GTK_TABLE(table), clist, 2, 15, 4, 12);

    //调节4个title的位置
    gtk_clist_set_column_width(clist, 0, 140);
    gtk_clist_set_column_width(clist, 1, 80);


    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

void refill_clist() {
    for (i = 0; i < 5; ++i) {
        resident_data[0] = g_strdup(residents[i].name);
        resident_data[1] = g_strdup_printf("%d", residents[i].building_number);
        resident_data[2] = g_strdup_printf("%d", residents[i].room_number);
        resident_data[3] = g_strdup_printf("%.2f", residents[i].payment_amount);
        gtk_clist_append(GTK_CLIST(clist), (gchar **) resident_data);
    }
}

void on_search_clicked(GtkWidget *button, gpointer user_data) {
    // 清空列表
    gtk_clist_clear(GTK_CLIST(user_data));
    refill_clist();
}*/
