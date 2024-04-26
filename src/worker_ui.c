//
// Created by 小灰灰 on 24-4-23.
//

#include "../include/ui.h"


#include <gtk/gtk.h>

size_t i;

password_data user_name;

void cleaner_return(GtkWidget *button, gpointer user_data) {
    gtk_widget_destroy(user_data);
    login_main(0,NULL);
}

//保洁页面
int cleaner_main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    // 创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "保洁界面");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //将生成的窗口居中
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    // 创建一个10x10的布局容器
    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    //把容器添加到窗口中去
    gtk_container_add(GTK_CONTAINER(window), table);

    //创建6个标签
    GtkWidget *label1_1 = gtk_label_new("用户信息");
    GtkWidget *label1_2 = gtk_label_new("操作选项");
    GtkWidget *label2_1 = gtk_label_new("姓名");
    GtkWidget *label3_1 = gtk_label_new("工作区域");
    GtkWidget *label2_2 = gtk_label_new("");
    GtkWidget *label3_2 = gtk_label_new("");

    //创建一个按钮
    GtkWidget *button1 = gtk_button_new_with_label("密码维护");
    g_signal_connect(button1, "clicked", G_CALLBACK(password_change), NULL);
    GtkWidget *button2 = gtk_button_new_with_label("返回上一级");
    g_signal_connect(button2, "clicked", G_CALLBACK(cleaner_return), window);


    //对标签和按钮系统性定位
    gtk_table_attach(GTK_TABLE(table), label1_1, 2, 11, 2, 4,
                    GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), label1_2, 10, 18, 2, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), label2_1, 2, 7, 4, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), label2_2, 6, 11, 4, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), label3_1, 2, 7, 6, 8,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), label3_2, 6, 11, 6, 8,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_table_attach(GTK_TABLE(table), button1, 12, 17, 5, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table), button2, 15, 18, 7, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    // 显示所有窗口部件
    gtk_widget_show_all(window);
    //运行主循环
    gtk_main();

    return 0;
}



//保安界面兼二级跳转
#define COLUMN_ID    0//列索引
#define COLUMN_NAME  1//列索引
gboolean window1_opened = FALSE;//标记窗口1是否已打开
gboolean window3_opened = FALSE;//标记窗口3是否已打开
gboolean window4_opened = FALSE;//标记窗口4是否已打开

//window1——记录选中的排列方式的ID
static int last_selected_id = -1;

//window1——window1中双击事件响应
static void on_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {

    //控件，可操作；树形数据结构
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter iter;

    // 确保路径有效，并从模型中获取对应行的迭代器，如果能够成功获取到迭代器，则条件为真
    //通过给定的模型（model）和路径（path），获取对应的迭代器（iter）
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        int id;
        gtk_tree_model_get(model, &iter, COLUMN_ID, &id, -1);

        // 更新last_selected_id
        last_selected_id = id;

        // 现在，变量`id`包含了被激活行的ID
        g_print("Activated row with ID: %d\n", id);
    }
}


//window1——window1中删除按钮响应，user_data传入tree_view以获取该GtkTreeView控件的数据模型
static void on_delete_button_clicked(GtkButton *button, gpointer user_data) {
    if (last_selected_id != -1) {

        GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(user_data));
        GtkTreeIter iter;

        // 获取模型中的第一个迭代器存在iter中
        gboolean found = gtk_tree_model_get_iter_first(model, &iter);
        // 遍历模型，查找与last_selected_id匹配的行
        while (found) {
            int id;
            gtk_tree_model_get(model, &iter, COLUMN_ID, &id, -1);

            if (id == last_selected_id) {
                // 找到了匹配的行，移除它
                //将指定行从列表存储中删除，并释放相关资源
                gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
                break;
            }
            //函数返回一个布尔值，如果成功找到下一个节点，则返回TRUE，否则返回FALSE。
            // 当返回FALSE时，表示已经遍历完了树型模型中的所有节点。
            found = gtk_tree_model_iter_next(model, &iter);
        }

        // 已清除选中行,重新标记为-1
        last_selected_id = -1;

        // 重新排列剩余数据的COLUMN_ID为正常顺序
        int new_id = 1;
        //获取第一个迭代器
        found = gtk_tree_model_get_iter_first(model, &iter);
        while (found) {
            //把当前迭代器列的值为COLUMU_ID的值设置为new_id
            gtk_list_store_set(GTK_LIST_STORE(model), &iter, COLUMN_ID, new_id++, -1);
            //获取下一个迭代器
            found = gtk_tree_model_iter_next(model, &iter);
        }

    } else {
        //单击或者未选中行时报错
        g_print("No row is currently selected.\n");
    }
}

//仅关闭窗口1，重新标记window1为未打开
void close_window1_only(GtkWidget *window1) {
    gtk_widget_destroy(window1);
    window1=NULL;
    window1_opened=FALSE;
    gtk_main();
}

//创建window1
GtkWidget *window1=NULL;
static void generate_window1(void){
    // 创建主窗口
    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(window1), 10);
    // 设置窗口的基本属性和信号处理
    gtk_window_set_title(GTK_WINDOW(window1), "完成业主报修");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 300);
    g_signal_connect(window1, "destroy", G_CALLBACK(close_window1_only), NULL);

    // 创建GtkListStore
    GtkListStore *list_store = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);

    // 向GtkListStore中添加数据（此处仅为示例，实际应用中应根据需要添加数据）
    GtkTreeIter iter;
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter,
                       COLUMN_ID,   1,
                       COLUMN_NAME, "Item 1",
                       -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter,
                       COLUMN_ID,   2,
                       COLUMN_NAME, "Item 2",
                       -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter,
                       COLUMN_ID,   3,
                       COLUMN_NAME, "Item 3",
                       -1);

    // 创建GtkTreeView并设置数据模型
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));

    // 在列表视图等组件中渲染文本
    GtkCellRenderer *renderer_text = gtk_cell_renderer_text_new();

    //创建列，添加到tree_view视图中
    GtkTreeViewColumn *column_id = gtk_tree_view_column_new_with_attributes("工作编号", renderer_text, "text", COLUMN_ID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_id);

    GtkTreeViewColumn *column_name = gtk_tree_view_column_new_with_attributes("工作内容", renderer_text, "text", COLUMN_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_name);

    // 为GtkTreeView添加“row-activated”信号处理器，即双击时获取其id
    g_signal_connect(tree_view, "row-activated", G_CALLBACK(on_row_activated), NULL);

    // 为了在窗口中正常显示，将GtkTreeView放入GtkScrolledWindow中，并设置固定大小
    //数据过多时可进行滚轮滑动，没有父窗口
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);
    gtk_widget_set_size_request(scrolled_window, 200, 200);

    // 使用GtkVBox布局，vbox->window1
    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window1), vbox);

    // 添加GtkScrolledWindow到VBox，即scrolled_window->vbox
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    //删除按键
    GtkWidget *delete_button = gtk_button_new_with_label("删除");
    g_signal_connect(delete_button, "clicked", G_CALLBACK(on_delete_button_clicked), tree_view);

    // 创建一个HBox用于水平布局按钮，delete_button->hbox->vbox
    GtkWidget *hbox = gtk_hbox_new(FALSE, 10);  // 设置间距为5
    gtk_box_pack_start(GTK_BOX(hbox), delete_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // 显示窗口
    gtk_widget_show_all(window1);
};


//window3——为window3的下拉菜单创建选项
typedef struct {
    const gchar *text;
    int id;
} MenuItem;
MenuItem sort_options[] = {
        {"按最后一次缴费时间", 1},
        {"按居住的楼栋号", 2},
        {"按姓名", 3},
        {"按倒序",4},
        {"按正序",5}
};

//window3——下拉菜单排序选项
GtkWidget *file_menu_item1=NULL;
GtkWidget *file_menu_item2=NULL;


//替换下拉菜单标签名
void update_menu_item_label(GtkWidget *menu_item, const gchar *new_label) {
    gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(menu_item))), new_label);
}

//按最后一次缴费时间
void on_paytime_activated(GtkMenuItem *item, gpointer user_data) {
    update_menu_item_label(file_menu_item1, "按最后一次缴费时间");
    printf("Based on the last time of paying\n");
}

//按楼栋号
void  on_building_activated(GtkMenuItem *item, gpointer user_data) {
    update_menu_item_label(file_menu_item1, "按居住的楼栋号");
    printf("Based on the region of the building\n");
}

//按名字
void on_name_activated(GtkMenuItem *item, gpointer user_data) {
    update_menu_item_label(file_menu_item1, "按名字");
    printf("Based on the name of guards\n");
}

//按倒序
void on_inverted_order_activated(GtkMenuItem *item, gpointer user_data){
    update_menu_item_label(file_menu_item2, "按倒序");
    printf("Based on the inverted order\n");
}

//按顺序
void on_sequence_activated(GtkMenuItem *item, gpointer user_data){
    update_menu_item_label(file_menu_item2, "按顺序");
    printf("Based on the sequence\n");
}


typedef struct {
    int i;
    int j;
}temp_data;

temp_data da;
temp_data *data = &da;

//window3——解析数据
list_link_head result;
char *resident_data[4];

static int menu1_id=-1;
static int menu2_id=-1;

//仅关闭窗口3，重新标记window3为未打开
void close_window3_only(GtkWidget *window3) {
    gtk_widget_destroy(window3);
    window3=NULL;
    window3_opened=FALSE;
    menu1_id=-1;
    menu2_id=-1;
    gtk_main();
}

void on_combobox_changed() {
    printf("%d %d\n", menu1_id,menu2_id);
}


void return11(GtkWidget *widget){
    data->i = 1;
}

void return12(GtkWidget *widget){
    data->i = 2;
}

void return13(GtkWidget *widget){
    data->i = 3;
}

void return21(GtkWidget *widget){
    data->j = 1;
}

void return22(GtkWidget *widget){
    data->j = 2;
}

static GtkWidget *entry;
static GtkWidget *clist;
static gchar *title[4] = {"姓名", "楼栋号", "房间号", "缴费费用"};


//window3——创建窗口3
GtkWidget *window3 = NULL;
static void generate_window3(void) {
    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window3), "业主账单查询");
    gtk_window_set_default_size(GTK_WINDOW(window3), 600, 400);
    g_signal_connect(G_OBJECT(window3), "destroy", G_CALLBACK(close_window3_only), NULL);
    //生成在屏幕中央
    gtk_window_set_position(GTK_WINDOW(window3), GTK_WIN_POS_CENTER);

    // 创建一个10x20的布局容器
    GtkWidget *table3 = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window3), table3);


    GtkWidget *label1 = gtk_label_new("姓名");
    GtkWidget *label2 = gtk_label_new("楼栋号");
    GtkWidget *label3 = gtk_label_new("房间号");
    GtkWidget *label4 = gtk_label_new("缴费费用");

    gtk_table_attach(GTK_TABLE(table3), label1, 2, 5, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table3), label2, 6, 9, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table3), label3, 10, 13, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table3), label4, 14, 17, 3, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    // 创建菜单，并添加到窗口
    GtkWidget *menubar1 = gtk_menu_bar_new();
    gtk_container_add(GTK_CONTAINER(window3), menubar1);

    // 创建“排列方式”菜单项及其子菜单项
    GtkWidget *combo1 = gtk_combo_box_new_text();

    //下拉菜单
    for (size_t i = 0; i < 3; ++i) {
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), sort_options[i].text);
    }

    // 连接“changed”信号处理程序，根据需要实现相应的排序逻辑
    g_signal_connect(combo1, "changed", G_CALLBACK(on_combobox_changed), NULL);

    // 创建“排列方式”菜单项，并将 combo1 添加到其右侧
    file_menu_item1 = gtk_menu_item_new_with_mnemonic("排列方式");
    gtk_container_add(GTK_CONTAINER(file_menu_item1), combo1);
    gtk_misc_set_alignment(GTK_MISC(combo1), 0.0, 0.5);
    gtk_widget_show(combo1);
    GtkWidget *file_menu1 = gtk_menu_new();

    // 将组合框添加到表格
    // 将 combo1 设置为 file_menu_item1 的子菜单
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item1), combo1);

    GtkWidget *building_item = gtk_menu_item_new_with_label("按居住的楼栋号");
    g_signal_connect(building_item, "activate", G_CALLBACK(return11), NULL);
    g_signal_connect(building_item, "activate", G_CALLBACK(on_building_activated), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu1), building_item);

    GtkWidget *name_item = gtk_menu_item_new_with_label("按姓名");
    g_signal_connect(name_item, "activate", G_CALLBACK(return12), NULL);
    g_signal_connect(name_item, "activate", G_CALLBACK(on_name_activated), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu1), name_item);

    GtkWidget *paytime_item = gtk_menu_item_new_with_label("按最后一次缴费时间");
    g_signal_connect(paytime_item, "activate", G_CALLBACK(return13), NULL);
    g_signal_connect(paytime_item, "activate", G_CALLBACK(on_paytime_activated), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu1), paytime_item);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item1), file_menu1);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar1), file_menu_item1);
    gtk_table_attach(GTK_TABLE(table3), menubar1, 1, 6,1 , 2,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);



    // 创建“排列方式”菜单项及其子菜单项
    GtkWidget *combo2 = gtk_combo_box_new_text();

    //下拉菜单
    for (size_t i = 3; i < 5; ++i) {
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo2), sort_options[i].text);
    }

    // 连接“changed”信号处理程序，根据需要实现相应的排序逻辑
    g_signal_connect(combo2, "changed", G_CALLBACK(on_combobox_changed), NULL);


    // 创建“正序倒序”菜单项，并将 combo2 添加到其右侧
    file_menu_item2 = gtk_menu_item_new_with_mnemonic("正序倒序");
    gtk_container_add(GTK_CONTAINER(file_menu_item2), combo2);
    gtk_misc_set_alignment(GTK_MISC(combo2), 0.5, 1.0);
    gtk_widget_show(combo2);
    GtkWidget *file_menu2 = gtk_menu_new();

    // 将组合框添加到表格
    // 将 combo2 设置为 file_menu_item2 的子菜单
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item2), combo2);


    GtkWidget *inverted_order_item = gtk_menu_item_new_with_label("按倒序");
    g_signal_connect(inverted_order_item, "activate", G_CALLBACK(return21), NULL);
    g_signal_connect(inverted_order_item, "activate", G_CALLBACK(on_inverted_order_activated), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu2), inverted_order_item);

    GtkWidget *sequence_item = gtk_menu_item_new_with_label("按顺序");
    g_signal_connect(sequence_item, "activate", G_CALLBACK(return22), NULL);
    g_signal_connect(sequence_item, "activate", G_CALLBACK(on_sequence_activated), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu2), sequence_item);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item2), file_menu2);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar1), file_menu_item2);



    //输入框
    entry = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table3), entry, 6, 14, 1, 3);
    // 将输入框添加到表格
    gtk_table_attach_defaults(GTK_TABLE(table3), entry, 6, 14, 0, 1);


    GtkWidget *button = gtk_button_new_with_label("搜索");
    gtk_table_attach(GTK_TABLE(table3), button, 14, 17, 1, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);


    gtk_table_set_row_spacings(GTK_TABLE(table3), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table3), 30);



    clist = gtk_clist_new_with_titles(4, title);
    gtk_table_attach_defaults(GTK_TABLE(table3), clist, 2, 17, 4, 9);

    //调节4个title的位置
    gtk_clist_set_column_width(clist, 0, 80);
    gtk_clist_set_column_width(clist, 1, 80);
    gtk_clist_set_column_width(clist, 2, 80);
    gtk_clist_set_column_width(clist, 3, 80);

    //点击时清空列表，刷新居民信息
    void on_search_clicked(GtkWidget *button, gpointer user_data);
    g_signal_connect(button, "clicked", G_CALLBACK(on_search_clicked), clist);

    gtk_widget_show_all(window3);

}



//仅关闭窗口4，重新标记window4为未打开
void close_window4_only(GtkWidget *window4) {
    gtk_widget_destroy(window4);
    window4=NULL;
    window4_opened=FALSE;
    gtk_main();
}


//window4——创建window4
GtkWidget *window4=NULL;
static void generate_window4(void) {
    window4 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window4), "未缴费用户查询");
    gtk_window_set_default_size(GTK_WINDOW(window4), 600, 400);
    g_signal_connect(G_OBJECT(window4), "destroy", G_CALLBACK(close_window4_only), window4);

    gtk_window_set_position(GTK_WINDOW(window4), GTK_WIN_POS_CENTER);

    // 创建一个10x10的布局容器
    GtkWidget *table4 = gtk_table_new(12, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window4), table4);

    char *str[3]={"1","2","3"};
    GtkWidget *label1 = gtk_label_new("用户姓名");
    GtkWidget *label2 = gtk_label_new("楼栋号");
    GtkWidget *label3 = gtk_label_new("房间号");
    GtkWidget *label4 = gtk_label_new(str[0]);
    GtkWidget *label5 = gtk_label_new(str[1]);
    GtkWidget *label6 = gtk_label_new(str[2]);

    gtk_table_attach(GTK_TABLE(table4), label1, 2, 10, 2, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table4), label2, 2, 10, 5, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table4), label3, 2, 10, 8, 10,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table4), label4, 11, 18, 2, 4,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table4), label5, 11, 18, 5, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table4), label6, 11, 18, 8, 10,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);



    gtk_table_set_row_spacings(GTK_TABLE(table4), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table4), 30);

    // 显示所有窗口部件
    gtk_widget_show_all(window4);
}

void (*generate_window1_ptr)(void)=generate_window1;
void on_button1_clicked(GtkButton *button, gpointer *user_data) {
    if (!window1_opened&&!window3_opened) {
        window1_opened = TRUE;
        generate_window1();
    }
}


void (*generate_window3_ptr)(void) = generate_window3;
void on_button3_clicked(GtkButton *button, gpointer *user_data) {
    if (!window3_opened&&!window1_opened&&!window4_opened) {
        window3_opened = TRUE;
        generate_window3();
    }
}


void (*generate_window4_ptr)(void) = generate_window4;
void on_button4_clicked(GtkButton *button, gpointer *user_data) {
    if (!window4_opened&&!window3_opened&&!window1_opened) {
        window4_opened = TRUE;
        generate_window4();
    }
}
void on_button5_clicked(GtkButton *button, gpointer *user_data) {
    gtk_widget_destroy(user_data);
    login_main(0,NULL);
}


list guard_information;
int guard_main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    guard_information= user_info_query(&database,user_name.username);
    char *Guard_infor[4];
    int i;
    for(i=0;i<3;i++){
        Guard_infor[i]=list_get(char*,guard_information.data,i+2);
    }


    // 创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "保安界面");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // 创建一个10x10的布局容器
    GtkWidget *table1 = gtk_table_new(16, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table1);

    //创建8个标签
    GtkWidget *label1_1 = gtk_label_new("用户信息");
    GtkWidget *label1_2 = gtk_label_new("操作选项");
    GtkWidget *label2_1 = gtk_label_new("姓名");
    GtkWidget *label3_1 = gtk_label_new("工作区域");
    GtkWidget *label4_1 = gtk_label_new("工作时间");
    GtkWidget *label5_1 = gtk_label_new("未缴费用户数量");



    GtkWidget *label2_2 = gtk_label_new(Guard_infor[0]);
    GtkWidget *label3_2 = gtk_label_new(Guard_infor[1]);
    GtkWidget *label4_2 = gtk_label_new(Guard_infor[2]);
    GtkWidget *label5_2 = gtk_label_new("");

    //创建3个按钮
    GtkWidget *button1 = gtk_button_new_with_label("完成业主报修");
    GtkWidget *button2 = gtk_button_new_with_label("密码维护");
    GtkWidget *button3 = gtk_button_new_with_label("业主账单查询");
    GtkWidget *button4 = gtk_button_new_with_label("未缴费用户查询");
    GtkWidget *button5 = gtk_button_new_with_label("返回上一级");


    //系统定位
    gtk_table_attach(GTK_TABLE(table1), label1_1, 2, 11, 2, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label1_2, 10, 18, 2, 5,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label2_1, 2, 7, 5, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label2_2, 6, 11, 5, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label3_1, 2, 7, 7, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label3_2, 6, 11, 7, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label4_1, 2, 7, 9, 11,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label4_2, 6, 11, 9, 11,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label5_1, 2, 7, 11, 14,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), label5_2, 6, 11, 11, 14,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);


    gtk_table_attach(GTK_TABLE(table1), button1, 12, 17, 5, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), button2, 12, 17, 7, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), button3, 12, 17, 9, 11,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), button4, 12, 17, 11, 13,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), button5, 15, 18, 13, 15,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_table_set_row_spacings(GTK_TABLE(table1), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table1), 30);


    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), window);
    g_signal_connect(button2, "clicked", G_CALLBACK(password_change), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button3_clicked), window);
    g_signal_connect(button4, "clicked", G_CALLBACK(on_button4_clicked), window);
    g_signal_connect(button5, "clicked", G_CALLBACK(on_button5_clicked), window);


    // 显示所有窗口部件
    gtk_widget_show_all(window);
    //运行主循环
    gtk_main();
}


void refill_clist() {
    printf("YES\n");
    temp_data *a = (temp_data *) data;
    int m = a->i;
    int n = a->j;
    int i, j;
    printf("%d %d\n", m, n);
    if(n==2){
        if(m==1){
            result = database_qsort(&database, "resident","region");
            struct list_link_node* cur=result.next;
            for (i = 0; i < result.length ; i++) {
                resident_data[0] = list_get(char*, &(cur->data),2);
                resident_data[1] = list_get(char*, &(cur->data),3);
                resident_data[2] = list_get(char*, &(cur->data),4);
                resident_data[3] = list_get(char*, &(cur->data),5);
                gtk_clist_append(GTK_CLIST(clist), (gchar **) resident_data);
                cur=cur->next;
            }
        }
        else if(m==2){
            result = database_qsort(&database, "resident","name");
            struct list_link_node* cur=result.next;
            for (i = 0; i < result.length ; i++) {
                resident_data[0] = list_get(char*, &(cur->data),2);
                resident_data[1] = list_get(char*, &(cur->data),3);
                resident_data[2] = list_get(char*, &(cur->data),4);
                resident_data[3] = list_get(char*, &(cur->data),5);
                gtk_clist_append(GTK_CLIST(clist), (gchar **) resident_data);
            }
        }
        else{
            result = database_qsort(&database, "resident","fee");
            struct list_link_node* cur=result.next;
            for (i = 0; i < result.length ; i++) {
                resident_data[0] = list_get(char*, &(cur->data),2);
                resident_data[1] = list_get(char*, &(cur->data),3);
                resident_data[2] = list_get(char*, &(cur->data),4);
                resident_data[3] = list_get(char*, &(cur->data),5);
                gtk_clist_append(GTK_CLIST(clist), (gchar **) resident_data);
            }
        }
    }
    else{
        if(m==1){
            result = database_qsort_reverse(&database, "resident","region");
            struct list_link_node* cur=result.next;
            for (i = 0; i < result.length ; i++) {
                resident_data[0] = list_get(char*, &(cur->data),2);
                resident_data[1] = list_get(char*, &(cur->data),3);
                resident_data[2] = list_get(char*, &(cur->data),4);
                resident_data[3] = list_get(char*, &(cur->data),5);
                gtk_clist_append(GTK_CLIST(clist), (gchar **) resident_data);
            }
        }
        else if(m==2){
            result = database_qsort_reverse(&database, "resident","name");
            struct list_link_node* cur=result.next;
            for (i = 0; i < result.length ; i++) {
                resident_data[0] = list_get(char*, &(cur->data),2);
                resident_data[1] = list_get(char*, &(cur->data),3);
                resident_data[2] = list_get(char*, &(cur->data),4);
                resident_data[3] = list_get(char*, &(cur->data),5);
                gtk_clist_append(GTK_CLIST(clist), (gchar **) resident_data);
            }
        }
        else{
            result = database_qsort_reverse(&database, "resident","fee");
            struct list_link_node* cur=result.next;
            for (i = 0; i < result.length ; i++) {
                resident_data[0] = list_get(char*, &(cur->data),2);
                resident_data[1] = list_get(char*, &(cur->data),3);
                resident_data[2] = list_get(char*, &(cur->data),4);
                resident_data[3] = list_get(char*, &(cur->data),5);
                gtk_clist_append(GTK_CLIST(clist), (gchar **) resident_data);
            }
        }
    }
}


void on_search_clicked(GtkWidget *button, gpointer user_data) {
    // 清空列表
    printf("YES\n");
    gtk_clist_clear(GTK_CLIST(user_data));
    refill_clist();
}