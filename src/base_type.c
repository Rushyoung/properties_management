#ifndef DEBUG
#include "base_type.h"
#endif

#include <stdlib.h>
#include <string.h>


/**
 * @brief 创建一个链表
 * @param sizeof(type) 类型的大小
 * @return list 返回创建的链表
 */
list list_create_by(int sizeof_type) {
    list l;
    l._type_size = sizeof_type;
    l.length = 0;
    l._capacity = 8;
    l._data = malloc(sizeof_type * l._capacity);
    return l;
}


/**
 * @brief 设置链表的元素
 * @param l 链表
 * @param index 索引
 * @param value 值
 */
void list_set_ptr(list* l, int index, void* value) {
    if( index < 0 || index >= l->length){
        return;
    }
    memcpy(l->_data + index * l->_type_size, value, l->_type_size);
}


/**
 * @brief 获取链表的元素
 * @param l 链表
 * @param index 索引
 * @return void* 返回索引对应的元素
 */
void*list_get_ptr(list* l, int index) {
    if( index < 0 || index >= l->_capacity){
        return NULL;
    }
    return l->_data + index * l->_type_size;
}

void list_append_ptr(list* l, void* value) {
    if( l->length >= l->_capacity){
        list_expand(l);
    }
    memcpy(l->_data + l->length * l->_type_size, value, l->_type_size);
    l->length++;
}


/**
 * @brief 扩容链表
 * @param l 链表
 */
void list_expand(list* l) {
    if(l->_capacity < 64){
        l->_capacity *= 2;
    } else {
        l->_capacity += 32;
    }
    l->_data = realloc(l->_data, l->_type_size * l->_capacity);
}


/**
 * @brief 释放链表
 * @param l 链表
*/
void list_free(list* l) {
    free(l->_data);
}


/**
 * @brief 创建一个映射
 * @return map 返回创建的映射
 */
map map_create() {
    map d;
    d._capacity = 16;
    d.keys = malloc(sizeof(str) * d._capacity);
    for(int i = 0; i < d._capacity; i++){
        d.keys[i] = NULL;
    }
    d.values = malloc(sizeof(int) * d._capacity);
    return d;
}


/**
 * @brief 设置映射的键值对
 * @param d 映射
*/
void map_set(map* d, str key, int value) {
    int is_set = 0;
    for(int i = 0; i < d->_capacity; i++){
        if(is_set == 0 && d->keys[i] == NULL){
            d->keys[i] = malloc(strlen(key) + 1);
            strcpy(d->keys[i], key);
            d->values[i] = value;
            is_set = 1;
            continue;
        }
        if(is_set == 0 && d->keys[i] != NULL && strcmp(d->keys[i], key) == 0 ){
            d->values[i] = value;
            return;
        }
        if(is_set == 1 && d->keys[i] != NULL && strcmp(d->keys[i], key) == 0){
            free(d->keys[i]);
            d->keys[i] = NULL;
            d->values[i] = 0;
            return;
        }
    }
    if(is_set == 0){
        map_expand(d);
        map_set(d, key, value);
    }
}


/**
 * @brief 获取映射的值
 * @param d 映射
 * @param key 键
 * @return int 返回键对应的值
 */
int map_get(map* d, str key) {
    for(int i = 0; i < d->_capacity; i++){
        if(d->keys[i] == NULL){
            continue;
        }
        if(strcmp(d->keys[i], key) == 0){
            return d->values[i];
        }
    }
    return 0;
}


/**
 * @brief 删除映射的键值对
 * @param d 映射
 * @param key 键
 */
void map_remove(map* d, str key) {
    for(int i = 0; i < d->_capacity; i++){
        if(strcmp(d->keys[i], key) == 0){
            free(d->keys[i]);
            d->keys[i] = NULL;
            return;
        }
    }
}


/**
 * @brief 扩容映射
 * @param d 映射
 */
void map_expand(map* d) {
    d->_capacity += 16;
    d->keys = realloc(d->keys, sizeof(str) * d->_capacity);
    for(int i=d->_capacity - 16; i < d->_capacity; i++){
        d->keys[i] = NULL;
    }
    d->values = realloc(d->values, sizeof(int) * d->_capacity);
}


/**
 * @brief 释放映射
 * @param d 映射
*/
void map_free(map* d) {
    for(int i = 0; i < d->_capacity; i++){
        free(d->keys[i]);
    }
    free(d->keys);
    free(d->values);
}


/**
 * @brief 创建一个字典
 * @return dict 返回创建的字典
 */
dict dict_create() {
    dict d;
    d._capacity = 16;
    d.keys   = malloc(sizeof(str) * d._capacity);
    d.values = malloc(sizeof(str) * d._capacity);
    for(int i = 0; i < d._capacity; i++){
        d.keys[i]   = NULL;
        d.values[i] = NULL;
    }
    return d;
}


/**
 * @brief 设置字典的键值对
 * @param d 字典
 */
void dict_set(dict* d, str key, str value) {
    int is_set = 0;
    for(int i = 0; i < d->_capacity; i++){
        if(is_set == 0 && d->keys[i] == NULL){
            d->keys[i] = malloc(strlen(key) + 1);
            strcpy(d->keys[i], key);
            d->values[i] = malloc(strlen(value) + 1);
            strcpy(d->values[i], value);
            is_set = 1;
            continue;
        }
        if(is_set == 0 && d->keys[i] != NULL && strcmp(d->keys[i], key) == 0 ){
            free(d->values[i]);
            d->values[i] = malloc(strlen(value) + 1);
            strcpy(d->values[i], value);
            return;
        }
        if(is_set == 1 && d->keys[i] != NULL && strcmp(d->keys[i], key) == 0){
            free(d->keys[i]);
            d->keys[i] = NULL;
            free(d->values[i]);
            d->values[i] = NULL;
            return;
        }
    }
    if(is_set == 0){
        dict_expand(d);
        dict_set(d, key, value);
    }
}


/**
 * @brief 获取字典的值
 * @param d 字典
 * @param key 键
 * @return str 返回键对应的值
 */
str dict_get(dict* d, str key) {
    for(int i = 0; i < d->_capacity; i++){
        if(d->keys[i] == NULL){
            continue;
        }
        if(strcmp(d->keys[i], key) == 0){
            return d->values[i];
        }
    }
    return NULL;
}


/**
 * @brief 删除字典的键值对
 * @param d 字典
 * @param key 键
 */
void dict_remove(dict* d, str key) {
    for(int i = 0; i < d->_capacity; i++){
        if(strcmp(d->keys[i], key) == 0){
            free(d->keys[i]);
            d->keys[i] = NULL;
            free(d->values[i]);
            d->values[i] = NULL;
            return;
        }
    }
}


/**
 * @brief 扩容字典
 * @param d 字典
 */
void dict_expand(dict* d) {
    d->_capacity += 16;
    d->keys   = realloc(d->keys, sizeof(str) * d->_capacity);
    d->values = realloc(d->values, sizeof(str) * d->_capacity);
    for(int i=d->_capacity - 16; i < d->_capacity; i++){
        d->keys[i]   = NULL;
        d->values[i] = NULL;
    }
}


/**
 * @brief 释放字典
 * @param d 字典
*/
void dict_free(dict* d) {
    for(int i = 0; i < d->_capacity; i++){
        free(d->keys[i]);
        free(d->values[i]);
    }
    free(d->keys);
    free(d->values);
}


/**
 * @brief 对一个字符串进行复制，同时自带内存回收机制
 * @param s 字符串
 * @return str 返回创建的字符串
 */
str string(str s) {
    const int STRING_EXTRA_LIMIT = 64;
    static int cursor = 0;
    static str strings[64] = {};
    if(strings[cursor] != NULL){
        free(strings[cursor]);
    }
    strings[cursor] = malloc(strlen(s) + 1);
    strcpy(strings[cursor], s);
    int id = cursor;
    cursor = (cursor + 1) % STRING_EXTRA_LIMIT;
    return strings[id];
}
