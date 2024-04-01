//
// Created by lzx on 2024/3/30.
//
#include "..\include\base_type.h"
#include <stdlib.h>
#include <string.h>


list list_create(int sizeof_type){
    list l;
    l.type_size = sizeof_type;
    l.capacity = 8;
    l.length = 0;
    l.data = malloc(l.capacity * sizeof_type);
    return l;
}
/**
 * index: 索引从,1开始
 * _data: 附加的数据
 */
void list_set(list* l, int index, void* _data){
    if(index < 0 || index >= l->length){
        return; // error process
    }
    memcpy(l->data + index * l->type_size, _data, l->type_size);
}

void* list_get(list* l, int index){
    if(index < 0 || index >= l->length){
        return NULL; // error process
    }
    return l->data + index * l->type_size;
}

void list_expand(list* l){
    if(l->capacity < 64){
        l->capacity *= 2;
    }
    else if(l->capacity >= 64){
        l->capacity += 32;
    }
    realloc(l->data, l->capacity);
}

void list_append(list* l, void* _data){
    if(l->length >= l->capacity){
        list_expand(l);
    }
    memcpy(l->data + l->type_size * l->length, _data, l->type_size);
    l->length++;
}


map map_create(){
    map m;
    m.capacity = 16;
    m.keys = malloc(sizeof(char*) * m.capacity);
    for(int i = 0; i < m.capacity; i++){
        m.keys[i] = NULL;
    }
    m.values = malloc(sizeof(int*) * m.capacity);
}