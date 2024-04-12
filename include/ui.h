#ifndef __UI_HEADER__
#define __UI_HEADER__

#include "base_type.h"

enum UI_TOKEN{
    UI_INPUT,
    UI_BLOCK,
    UI_BUTTON,
    UI_LINE,
    UI_TEXT,
    UI_HORIZONTAL,
    UI_VERTICAL
};
typedef enum UI_TOKEN ui_token;


typedef struct{
    double x;
    double y;
} ui_point;


typedef struct{
    int value;
    double relative;
    bool is_relative;
    ui_token type;
} ui_size; 

ui_size _ui_size_create_actual(int, ui_token);
ui_size _ui_size_create_relative(double, ui_token);
#define ui_size_create(v, t) \
    ({_Generic((v), \
        int: _ui_size_create_actual, \
        double: _ui_size_create_relative \
        float: _ui_size_create_relative \
    )(v, t);})
void ui_size_reset(ui_size*);


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


typedef struct{
    ui_point pos;
    char* goal_string;
    ui_size length;
} ui_input;
ui_input ui_input_register();
void ui_input_set(ui_input*, str, ui_point, ui_size);

typedef struct{
    ui_point pos;
    ui_size width;
    ui_size height;
} ui_block;
ui_block ui_block_register();
void ui_block_set(ui_block*, ui_point, ui_size, ui+size, int);

typedef struct{
    ui_point pos;
    char prompt[1024];
    ui_size length;
} ui_button;
ui_button ui_button_register();
void ui_button_set(ui_button*, str, ui_point, ui_size);
void ui_button_operate(ui_button*, int);

typedef struct{
    ui_point pos;
    ui_size length;
} ui_line;
ui_line ui_line_register();
void ui_line_set(ui_line*, ui_point, ui_size, ui_token);

typedef struct{
    ui_point pos;
    char* content;
} ui_text;


typedef struct{
    union{
        ui_input input;
        ui_block block;
        ui_button button;
        ui_line line;
        ui_text text;
    } unit;
    ui_token unit_type;
} component;

#endif
