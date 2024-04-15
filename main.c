#include <stdio.h>

#include "base_type.h"

#include "database.h"

#include "auth.h"

#include <gtk/gtk.h>

void login(str, str);

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
