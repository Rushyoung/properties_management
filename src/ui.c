#ifndef DEBUG
#include "ui.h"
#endif

#include <stdio.h>

#ifdef __linux__
#define wwwww
#elif defined(_WIN32)
#include <windows.h>
#endif

void ui_init(){
    _ui_stack.layouts = list_create( component );
    _ui_stack.is_root = true;
    _ui_stack.pref = NULL;
    _ui_stack.next = NULL;
    _ui_stack_top = &_ui_stack;
}

void console_utf8(){
#ifdef _WIN32
    system("chcp 65001");
#endif
}

void console_clear(){
#ifdef __linux__
    printf("\033[H\033[J");
#elif defined(_WIN32)
    system("clear");
#endif
}

void console_size(int width, int length){
#ifdef _WIN32
    char cmd[1024] = {};
    //TODO
#endif
}

void console_title(str title){
#ifdef _WIN32
    char cmd[1024] = {};
    sprintf(cmd, "title  %s", title);
    system(cmd);
#endif
}

void console_new(){
    ui_layout *new_layout = malloc(sizeof(ui_layout));
    new_layout->layouts = list_create( component );
    new_layout->is_root = false;
    new_layout->next    = NULL;
    new_layout->pref    = _ui_stack_top;
    _ui_stack_top->next = new_layout;
    _ui_stack_top = new_layout;
}

int console_mainloop(){
    ;
}

void console_destroy(){
    if(_ui_stack_top->is_root){
        return;
    }
    list_free(&(_ui_stack_top->layouts));
    ui_layout *pref_node = _ui_stack_top->pref;
    free(_ui_stack_top);
    _ui_stack_top = pref_node;
}


