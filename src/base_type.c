//
// Created by lzx on 2024/3/30.
//
//
#include "..\include\base_type.h"
#include <stdlib.h>
#include <string.h>

#define list_create_by_size(size) list_create(sizeof(size));

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
        perror("out of index");
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
str list_get_str(list* l, int index){
    if(index < 0 || index >= l->length){
        return NULL; // error process
    }
    return *(char**)(l->data + index * l->type_size);
}
void list_expand(list* l){
    if(l->capacity < 64){
        l->capacity *= 2;
    }
    else if(l->capacity >= 64){
        l->capacity += 32;
    }
    l->data = realloc(l->data, l->capacity * l->type_size);
}

void list_append(list* l, void* _data){
    if(l->length >= l->capacity){
        list_expand(l);
    }
    memcpy(l->data + l->type_size * l->length, _data, l->type_size);
    l->length++;
}

void list_free(list* l){
    free(l->data);
}

map map_create(){
    map m;
    m.capacity = 16;
    m.keys = malloc(sizeof(char*) * m.capacity);
    for(int i = 0; i < m.capacity; i++){
        m.keys[i] = NULL;
    }
    m.values = malloc(sizeof(int*) * m.capacity);
    return m;
}


void map_set(map* m, str key, int value){
    int is_set = 0;
    for(int i = 0; i < m->capacity; i++){
        if(m->keys[i] != NULL && strcmp(m->keys[i], key) == 0){
            m->values[i] = value;
            return;
        }
        if(is_set == 0 && m->keys[i] == NULL){
            m->keys[i] = malloc(strlen(key) + 1);
            strcpy(m->keys[i], key);
            m->values[i] = value;
            is_set = 1;
        }
    }
    if(is_set == 0){
        map_set(m, key, value);
    }
}

void map_expand(map* m){
    m->capacity += 16;
    m->keys = realloc(m->keys, m->capacity * sizeof(char*));
    if(m->keys == NULL) perror("mem");
    for(int i = m->capacity - 16; i < m->capacity; i++){
        m->keys[i] = NULL;
    }
    m->values = realloc(m->values, sizeof(int) * m->capacity);
    if(m->values == NULL) perror("mem");
}

int map_get(map* m, str key){
    for(int i = 0; i < m->capacity; i++){
        if(m->keys[i] == NULL){
            continue;
        }
        if(strcmp(m->keys[i], key) == 0){
            return m->values[i];
        }
    }
    return -1;
}

void map_remove(map* m, str key){
    for(int i = 0; i < m->capacity; i++){
        if(strcmp(m->keys[i], key) == 0){
            free(m->keys[i]);
            m->keys[i] = NULL;
            m->values[i] = 0;
            return;
        }
    }
}

void map_free(map* m){
    for(int i = 0; i < m->capacity; i++){
        free(m->keys[i]);
    }
    free(m->values);
    free(m->keys);
}

dict dict_create(){
    dict d;
    d.capacity = 16;
    d.keys = malloc(sizeof(char*) * d.capacity);
    d.values = malloc(sizeof(char*) * d.capacity);
    for(int i = 0; i < d.capacity; i++){
        d.keys[i] = NULL;
        d.values[i] = NULL;
    }
    return d;
}

void dict_set(dict* d, str key, str value){
    int is_set = 0;
    for(int i = 0; i < d->capacity; i++){
        if(is_set == 0 && d->keys[i] == NULL){
            d->keys[i] = malloc(sizeof(char*) * strlen(key));
            strcpy(d->keys[i], key);
            is_set = 1;
            d->values[i] = malloc(sizeof(char*) * strlen(value));
            strcpy(d->values[i], value);
            continue;
        }
        if(is_set == 0 && d->keys[i] != NULL && strcmp(d->keys[i], key) == 0){
            d->values[i] = malloc(sizeof(char*) * strlen(value));
            strcpy(d->values[i], value);
            return;
        }
        if(is_set == 1 && d->keys[i] && strcmp(d->keys[i], key) == 0){
            free(d->keys[i]);
            d->keys[i] = NULL;
            d->values[i] = NULL;
            return;
        }
    }
    if(is_set == 0){
        dict_expand(d);
        dict_set(d, key, value);
    }
}

void dict_expand(dict* d){
    d->capacity += 16;
    d->keys = realloc(d->keys, d->capacity);
    if(d->keys == NULL) perror("mem");
    d->values = realloc(d->values, d->capacity);
    if(d->values == NULL) perror("mem");
    for(int i = d->capacity-16; i < d->capacity; i++){
        d->keys[i] = NULL;
        d->values[i] = NULL;
    }
}



str dict_get(dict* d, str key){
    for(int i = 0; i < d->capacity; i++){
        if(strcmp(d->keys[i], key) == 0){
            return d->values[i];
        }
    }
    return NULL;
}

void dict_remove(dict* d, str key){
    for(int i = 0; i < d->capacity; i++){
        if(strcmp(d->keys[i], key) == 0){
            free(d->keys[i]);
            d->keys[i] = NULL;
            free(d->values[i]);
            d->values[i] = NULL;
            return;
        }
    }
}


void dict_free(dict* d){
    for(int i = 0; i < d->capacity; i++){
        free(d->keys[i]);
        free(d->values[i]);
    }
    free(d->keys);
    free(d->values);
}


str string(str s) {
    static int cursor = 0;
    static str strings[STRING_EXTRA_LIMIT] = {};
    static int str_len[STRING_EXTRA_LIMIT] = {};
    static int str_use[STRING_EXTRA_LIMIT] = {};
    int len = strlen(s);
    for(int i = 0; len <= STRING_SHORT_STD && i < STRING_EXTRA_LIMIT; i++){
        if(len == str_len[i] && strings[i] != NULL && strcmp(strings[i], s) == 0){
            str_use[i]++;
            return strings[i];
        }
    }
    for(; strings[cursor] != NULL;cursor = (cursor + 1) % STRING_EXTRA_LIMIT) {
        if (str_use[cursor] <= 1) {
            free(strings[cursor]);
            strings[cursor] = NULL;
            break;
        } else {
            str_use[cursor]--;
        }
    }
    strings[cursor] = malloc(len + 1);
    strcpy(strings[cursor], s);
    str_len[cursor] = len;
    str_use[cursor] = 1;
    int ret = cursor;
    cursor = (cursor + 1) % STRING_EXTRA_LIMIT;
    return strings[ret];
}
