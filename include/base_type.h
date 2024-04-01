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

void list_set(list*, int, void*);
void* list_get(list*, int);
void list_expand(list*);
void list_append(list*, void*);

typedef struct{
    int capacity;
    str *keys;
    int *values;
} map;

map map_create();
void map_set(map*, const str, int, )
#endif //PROPERTY_BASE_TYPE_H
