//
// Created by lzx on 2024/3/30.
// @brief: definition of base type(not public)
//

#ifndef PROPERTY_BASE_TYPE_H
#define PROPERTY_BASE_TYPE_H

typedef char* str;

typedef struct{
    int type_size;
    int capacity;
    int length;
    void* data;
} list;

list list_create(int);
#define list_get(type, l, index) ({*(type*)list_get_ptr((l), (index));})
void list_set(list*, int, void*);
void* list_get_ptr(list* l, int index);
str list_get_str(list*, int);
void list_expand(list*);
void list_append(list*, void*);
void list_free(list*);

typedef struct{
    int capacity;
    str *keys;
    int *values;
} map;

map map_create();
void map_set(map*, str, int);
void map_expand(map*);
int map_get(map*, str);
void map_remove(map*, str);
void map_free(map*);

typedef struct{
    int capacity;
    str* keys;
    str* values;
} dict;

dict dict_create();
void dict_set(dict*, str, str);
void dict_expand(dict*);
str dict_get(dict*, str);
void dict_remove(dict*, str);
void dict_free(dict*);


#define STRING_EXTRA_LIMIT 128
#define STRING_SHORT_STD 4
str string(str s);
#endif //PROPERTY_BASE_TYPE_H
