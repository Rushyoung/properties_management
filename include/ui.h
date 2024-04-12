#ifndef __UI_HEADER__
#define __UI_HEADER__

#include "base_type.h"

typedef struct{
    int x;
    int y;
} ui_point;

struct UI_LAYOUT{
    list layouts;
    bool is_root;
    struct UI_LAYOUT* pref;
    struct UI_LAYOUT* next;
} _ui_stack, *_ui_stack_top;
typedef struct UI_LAYOUT ui_layout;


void ui_init();

void console_utf8();
void console_clear();
void console_size(int, int);
void console_title(str);

void console_new();
int  console_mainloop();
void console_destroy();

enum{
    UI_INPUT,
    UI_BLOCK,
    UI_BUTTON,
    UI_LINE
};

typedef struct{
    ;
} ui_input;
ui_input ui_input_register();
void ui_input_set(input*, str, ui_point, int);

typedef struct{
    ;
} ui_block;
ui_block ui_block_register();
void ui_block_set(ui_block*, ui_point, int, int, int);

typedef struct{
    ;
} ui_button;
ui_button ui_button_register();
void ui_button_set(ui_button*, str, ui_point, int);
void ui_button_operate(ui_button*, int);

typedef struct{
    ;
} ui_line;
ui_line ui_line_register();
void ui_line_set(ui_line*, ui_point, int, int);


typedef struct{
    union{
        ui_input input;
        ui_block block;
        ui_button button;
        ui_line line;
    } unit;
    int unit_type;
} component;

#endif
