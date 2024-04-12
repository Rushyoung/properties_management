#ifndef DEBUG
#include "ui.h"
#endif

#include <stdio.h>

void ui_init(){
    _ui_stack.layouts = list_create( component );
    _ui_stack.is_root = true;
    _ui_stack.pref = NULL;
    _ui_stack.next = NULL;
    _ui_stack_top = &_ui_stack;
}

void console_utf8(){
    ;
}

void console_clear(){
    ;
}

void console_size(int width, int length){
    ;
}

void console_title(str title){
    ;
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


