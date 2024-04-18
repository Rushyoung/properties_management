#include <stdio.h>

#include "base_type.h"

#include "database.h"

#include "auth.h"

#include <gtk/gtk.h>

void login(str, str);

void init_create_database(){
    db goal = db_connect("data.db");

    map status = map_init( {"username", 16},
                           {"password", 16},
                           {"auth", 6} );
    db_insert_table(&goal, "status", status);
    map_free(&status);

    map user_info = map_init( {"username", 16},
                              {"phone", 16},
                              {"zone", 24} );
    db_insert_table(&goal, "user_info", user_info);
    map_free(&user_info);

    map fee = map_init( {"username", 16},
                        {"fee", 16},
                        {"paid", 16} );
    db_insert_table(&goal, "fee", fee);
    map_free(&fee);

    map log = map_init( {"username", 16},
                        {"time", 16},
                        {"action", 16},
                        {"amount", 16} );
    db_insert_table(&goal, "log", log);
    map_free(&log);

    list admin = list_init(string("admin"), string("ttakods"), string("0"));
    db_insert_lin(&goal, "status", admin);
    list_free(&admin);
}

int main() {
    gtk_init(NULL, NULL);
    // set windows
    login("username", "password");
}

void login(str username, str password){
    GtkBuilder *builder;
    GObject *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "C:/Users/wujun/Desktop/propert/assets/login.ui", NULL);

    window  = gtk_builder_get_object (builder, "window");

    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    //show the window
    gtk_widget_show_all (GTK_WIDGET(window));

    gtk_main ();
}
