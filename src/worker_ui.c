//
// Created by 小灰灰 on 24-4-23.
//

#include "../include/ui.h"


#include <gtk/gtk.h>

//保洁页面
int cleaner_main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    // 创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    // 创建一个10x10的布局容器
    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    //创建6个标签
    GtkWidget *label1_1 = gtk_label_new("用户信息");
    GtkWidget *label1_2 = gtk_label_new("操作选项");
    GtkWidget *label2_1 = gtk_label_new("姓名");
    GtkWidget *label3_1 = gtk_label_new("工作区域");
    GtkWidget *label2_2 = gtk_label_new("");
    GtkWidget *label3_2 = gtk_label_new("");

    //创建一个按钮
    GtkWidget *button = gtk_button_new_with_label("密码维护");
    g_signal_connect(button, "clicked", G_CALLBACK(password_change), NULL);


    //系统性定位
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

    gtk_table_attach(GTK_TABLE(table), button, 12, 17, 5, 7,
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

#define COLUMN_ID    0
#define COLUMN_NAME  1
gboolean window1_opened = FALSE;
gboolean window3_opened = FALSE;

typedef struct {
    const gchar *text;
    int id;
} MenuItem;

MenuItem sort_options[] = {
        {"按最后一次缴费时间", 1},
        {"按居住的楼栋号", 2},
        {"按姓名", 3}
};

static int last_selected_id = -1;

//双击
static void on_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter iter;

    // 确保路径有效，并从模型中获取对应行的迭代器
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        int id;
        gtk_tree_model_get(model, &iter, COLUMN_ID, &id, -1);

        // 更新last_selected_id
        last_selected_id = id;

        // 现在，变量`id`包含了被激活行的ID
        g_print("Activated row with ID: %d\n", id);
    }
}


static void on_delete_button_clicked(GtkButton *button, gpointer user_data) {
    if (last_selected_id != -1) {
        GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(user_data));
        GtkTreeIter iter;

        // 遍历模型，查找与last_selected_id匹配的行
        gboolean found = gtk_tree_model_get_iter_first(model, &iter);
        while (found) {
            int id;
            gtk_tree_model_get(model, &iter, COLUMN_ID, &id, -1);

            if (id == last_selected_id) {
                // 找到了匹配的行，移除它
                gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
                break;
            }

            found = gtk_tree_model_iter_next(model, &iter);
        }

        // 清零last_selected_id，表示已清除选中行
        last_selected_id = -1;

        // 重新排列剩余数据的COLUMN_ID
        int new_id = 1;
        found = gtk_tree_model_get_iter_first(model, &iter);
        while (found) {
            gtk_list_store_set(GTK_LIST_STORE(model), &iter, COLUMN_ID, new_id++, -1);
            found = gtk_tree_model_iter_next(model, &iter);
        }

    } else {
        g_print("No row is currently selected.\n");
    }
}

void close_window1_only(GtkWidget *window1) {
    gtk_widget_destroy(window1);
    window1=NULL;
    window1_opened=FALSE;
    gtk_main();
}

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

    // 创建列
    GtkCellRenderer *renderer_text = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column_id = gtk_tree_view_column_new_with_attributes("工作编号", renderer_text, "text", COLUMN_ID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_id);
    GtkTreeViewColumn *column_name = gtk_tree_view_column_new_with_attributes("工作内容", renderer_text, "text", COLUMN_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_name);

    // 为GtkTreeView添加“row-activated”信号处理器
    g_signal_connect(tree_view, "row-activated", G_CALLBACK(on_row_activated), NULL);


    // 为了在窗口中正常显示，将GtkTreeView放入GtkScrolledWindow中，并设置固定大小
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);
    gtk_widget_set_size_request(scrolled_window, 200, 200);

    // 使用GtkVBox布局
    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window1), vbox);

    // 创建一个空的顶部空间
    GtkWidget *top_space = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(top_space), 0.5, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), top_space, FALSE, FALSE, 0);


    // 添加GtkScrolledWindow
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);


    GtkWidget *delete_button = gtk_button_new_with_label("删除");
    g_signal_connect(delete_button, "clicked", G_CALLBACK(on_delete_button_clicked), tree_view);


    // 创建一个HBox用于水平布局两个按钮
    GtkWidget *hbox = gtk_hbox_new(FALSE, 10);  // 设置间距为5
    gtk_box_pack_start(GTK_BOX(hbox), delete_button, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // 显示窗口
    gtk_widget_show_all(window1);
};



void on_paytime_activated(GtkMenuItem *item, gpointer user_data) {
    printf("Based on the last time of paying\n");
}
void  on_building_activated(GtkMenuItem *item, gpointer user_data) {
    printf("Based on the region of the building\n");
}
void on_name_activated(GtkMenuItem *item, gpointer user_data) {
    printf("Based on the name of guards\n");
}

void on_combobox_changed(GtkComboBox *combo, gpointer user_data) {
    const gchar *selected_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo));
    int selected_id = -1;

    for (size_t i = 0; i < sizeof(sort_options) / sizeof(sort_options[0]); ++i) {
        if (strcmp(selected_text, sort_options[i].text) == 0) {
            selected_id = sort_options[i].id;
            break;
        }
    }

    if (selected_id != -1) {
        printf("Selected option with ID: %d\n", selected_id);

        // 根据选中的 ID 调用相应的排序函数或其他操作
        switch (selected_id) {
            case 1:
                on_paytime_activated(NULL,NULL);
                break;
            case 2:
                on_building_activated(NULL, NULL);
                break;
            case 3:
                on_name_activated(NULL, NULL);
                break;
            default:
                printf("error");
        }
    } else {
        printf("Invalid selection. Could not find a matching ID.\n");
    }
}

void close_window3_only(GtkWidget *window3) {
    gtk_widget_destroy(window3);
    window3=NULL;
    window3_opened=FALSE;
    gtk_main();
}

size_t i;
gchar *resident_data[4];

static GtkWidget *entry;
static GtkWidget *clist;
static gchar *title[4] = {"姓名", "楼栋号", "房间号", "缴费费用"};

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
GtkWidget *window3 = NULL;
static void generate_window3(void) {
    //二级界面_3
    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window3), "业主账单查询");
    gtk_window_set_default_size(GTK_WINDOW(window3), 600, 400);
    g_signal_connect(G_OBJECT(window3), "destroy", G_CALLBACK(close_window3_only), NULL);

    gtk_window_set_position(GTK_WINDOW(window3), GTK_WIN_POS_CENTER);

    // 创建一个16x10的布局容器
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


    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_container_add(GTK_CONTAINER(window3), menubar);

    // 创建“排列方式”菜单项及其子菜单项
    GtkWidget *combo = gtk_combo_box_new_text();


    for (size_t i = 0; i < sizeof(sort_options) / sizeof(sort_options[0]); ++i) {
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo), sort_options[i].text);
    }



// 连接“changed”信号处理程序，根据需要实现相应的排序逻辑
    g_signal_connect(combo, "changed", G_CALLBACK(on_combobox_changed), NULL);

// 将组合框添加到表格
    gtk_table_attach_defaults(GTK_TABLE(table3), combo, 0, 6, 0, 1);

// ... 创建输入框（entry）的代码不变

// 将输入框添加到表格
    gtk_table_attach_defaults(GTK_TABLE(table3), entry, 6, 14, 0, 1);



    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("排列方式");
    GtkWidget *file_menu = gtk_menu_new();

    GtkWidget *building_item = gtk_menu_item_new_with_label("按居住的楼栋号");
    g_signal_connect(building_item, "activate", G_CALLBACK(on_building_activated), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), building_item);

    GtkWidget *name_item = gtk_menu_item_new_with_label("按姓名");
    g_signal_connect(name_item, "activate", G_CALLBACK(on_name_activated), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), name_item);

    GtkWidget *paytime_item = gtk_menu_item_new_with_label("按最后一次缴费时间");
    g_signal_connect(paytime_item, "activate", G_CALLBACK(on_paytime_activated), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), paytime_item);


    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_menu_item);


    //输入框
    entry = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table3), entry, 6, 14, 1, 3);


    GtkWidget *button = gtk_button_new_with_label("搜索");
    gtk_table_attach(GTK_TABLE(table3), button, 14, 17, 1, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);


    gtk_table_set_row_spacings(GTK_TABLE(table3), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table3), 30);



    clist = gtk_clist_new_with_titles(4, title);
    gtk_table_attach_defaults(GTK_TABLE(table3), clist, 2, 17, 4, 12);

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

void (*generate_window1_ptr)(void)=generate_window1;
void on_button1_clicked(GtkButton *button, gpointer *user_data) {
    if (!window1_opened&&!window3_opened) {
        window1_opened = TRUE;
        generate_window1();
    }
}


void (*generate_window3_ptr)(void) = generate_window3;
void on_button3_clicked(GtkButton *button, gpointer *user_data) {
    if (!window3_opened&&!window1_opened) {
        window3_opened = TRUE;
        generate_window3();
    }
}

static void generate_windows3(){
    GtkWidget *window3=gtk_window_new(GTK_WINDOW_TOPLEVEL);
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    // 创建主窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
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
    GtkWidget *label2_2 = gtk_label_new("");
    GtkWidget *label3_2 = gtk_label_new("");
    GtkWidget *label4_2 = gtk_label_new("");
    GtkWidget *label5_2 = gtk_label_new("");

    //创建3个按钮
    GtkWidget *button1 = gtk_button_new_with_label("完成业主报修");
    GtkWidget *button2 = gtk_button_new_with_label("密码维护");
    GtkWidget *button3 = gtk_button_new_with_label("业主账单查询");

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


    gtk_table_attach(GTK_TABLE(table1), button1, 12, 17, 5, 8,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), button2, 12, 17, 8, 11,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(table1), button3, 12, 17, 11, 14,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    gtk_table_set_row_spacings(GTK_TABLE(table1), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table1), 30);


    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), window);
    g_signal_connect(button2, "clicked", G_CALLBACK(password_change), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button3_clicked), window);


    // 显示所有窗口部件
    gtk_widget_show_all(window);
    //运行主循环
    gtk_main();
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
}