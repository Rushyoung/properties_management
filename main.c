#include <stdio.h>

#include "base_type.h"

#include "database.h"
#include "auth.h"

#include "user_admin.h"
#include "user_worker.h"
#include "user_resident.h"

#include "UI.h"

void login(str, str);

int main() {
    // set windows
    console_utf8();
    console_clear();
    console_size(100, 80);
    console_title("Property Manager");
    // login
    char username[16]={}, password[16]={};
    while(true){
        login(username, password);
        auth account = auth_create(username, password);
        if(auth_is_login(account)){
            break;
        }
    }
    // load index page
}

void login(str username, str password){
    console_new();
    
    ui_input input_name = ui_input_register();
    ui_input_set(&input_name, username, {7,  8}, 20);
    ui_input input_word = ui_input_register();
    ui_input_set(&input_word, password, {12, 8}, 20);
    
    ui_button clear_button = ui_button_register();
    ui_button_set(&clear_button, "clear", {17,  8}, 8);
    ui_button_operate(&clear_button, UI_CLEAR_INPUT);

    ui_button check_button = ui_button_register();
    ui_button_set(&check_button, "login", {17, 18}, 8);
    ui_button_operate(&check_button, UI_EXIT);

    return console_mainloop();
}
