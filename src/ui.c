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

void widget_destory(GtkWidget *widget, gpointer data){
    gtk_widget_destroy(widget);
}

//创建登录页面
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
    gtk_label_set_markup(GTK_LABEL(label),"<span foreground='black'  font_desc='20'>欢迎使用世界树物业管理系统！</span>");

    GtkWidget *image = gtk_image_new_from_file("../asset/logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 3, 0, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

/* 创建一个按钮 */

    GtkWidget *button = gtk_button_new_with_label("登录");
    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button, 8, 10, 8, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND,5 , 5 );

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



//创建管理员页面
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    //创建主窗口
    char *shuchu = "NULL";
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    GtkWidget *image = gtk_image_new_from_file("../asset/logo2.png");
    gtk_table_attach(GTK_TABLE(table), image, 0, 3, 0, 3,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *label = gtk_label_new("admin");
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);

    GtkWidget *label1 = gtk_label_new("姓名：");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_table_attach(GTK_TABLE(table), label1, 1, 2, 5, 6,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    GtkWidget *label2 = gtk_label_new( shuchu);
    gtk_table_attach(GTK_TABLE(table), label2, 4, 10, 5, 10,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(label2), GTK_JUSTIFY_LEFT);
    gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);

    GtkWidget *button = gtk_button_new_with_label("liuhaizhu");
    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button, 1, 2, 6, 7,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_label_set_justify(GTK_LABEL(button), GTK_JUSTIFY_LEFT);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

//创建带有滚轮的输出窗口（模板）
int scoller_main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    //新建窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "世界树物业管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    //新建一个10x10的布局容器
    GtkWidget *table = gtk_table_new(10, 20, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    //设置布局容器的行和列的间距
    gtk_table_set_row_spacings(GTK_TABLE(table), 30);
    gtk_table_set_col_spacings(GTK_TABLE(table), 30);

    //创建一个带有滚动条的文本框
    GtkWidget *scoller = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scoller), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    //创建一个文本框
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);  // 设置自动换行

    //将文本框添加到滚动条中
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "fjkrs gnovzis hngiuyrsbnzg hiuybhiszubfg huyeszbghfuyhhb desuyfbg suyzehbg fuyhbegs aufbgua shhbfi  uyaghi ufhbnaiu8hf nbiuhahbn fiuab hnie uwyf\r\nhnai\r\n\r\nufhb\r\n\r\nniyah\r\nubfnihu\r\nyabnfi\r\nhuyabni\r\nufhybnva\r\ny8ubfg\r\nnviyahubnwfguvyhanbiuywfghbnvaiswuybhnfgviuyawfnbiyahbfniuajbhnfiyuanfhjiuyahbnfu9ajnbfuyhabnwihfbniuyahwbfniuahbnwgwfiuy8anwhmiuyfhbhnaiyuwfnhiaybnfyhiuawsneyfuybanwifawuhbfnhaegbdfuyhnahiubfhniuawhsnfyuiahbniufhbnauhyefhbniuyahsbeghifuhyasbgfuyhanbfiyughanwiuyfhgauwyfhnyuawehfnbuyabghfuyabhngfuy8abgnyfuhnbauyfbnijuwabfhniuanmfhouiahnfu9aiwmnjfhiuhjahhnmjoahfniuyajnbfhijabnfhijabnfhiuanbfiujaghbnfuijanbhfiuyhnbauoifhniuawhnfihjanwhiuyfbnaowuihfncucyahnbfiouajhbngwfuyianwmhfjisbeduhogvnbirsuydhgbnaijosuzdrgbhniurszjdnbgo8uy9dszghnijazswebghniouyersdbngiuhyswAZBGONFIVHJuAZSWBGNIYHUEWBNRSfgijkbhnosziouybnfgiuhjoserdhbgnfvhijkeszboguybnsdehijrgbisuyzhbnghisudberghiuvyszDBgiuyhbzsniouhyjgbnrsdoifhjugbnipejrsuzdhfgnbpuz8deiorsfbhngoipuy8defjrszbgntdeijoprsuyzfbngiopuydefhjrzsbhngiuygiuybhnzr6ezgs41zr8ds54g15+64z1drs56g14z56dr1ghbzdr41h58914dr984158dzr41h98d56r14h589d14rt895h6149d8rt4f1h895dz41r98ht4158drzf4hg789d41rh5894dz89rf5h4158dzsr41h896", -1);

    //将文本视图添加到滚动窗格中
    gtk_container_add(GTK_CONTAINER(scoller), text_view);  // 将文本视图添加到滚动窗格中
    gtk_table_attach(GTK_TABLE(table), scoller, 5, 6, 5, 10,GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 3, 3);

    GtkWidget *button = gtk_button_new_with_label("登录");
    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window_callback), NULL);
    gtk_table_attach(GTK_TABLE(table), button, 8, 10, 8, 9,
                     GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND,5 , 5 );


    gtk_widget_show_all(window);
    gtk_main();
}