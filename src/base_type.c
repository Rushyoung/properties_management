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
 * @brief 创建一个链表, 并初始化一些值
 * @param sizeof(type) 类型的大小
 * @param length 长度
 * @param values 值
 */
list list_init_by(int sizeof_type, int length, void* values) {
    list l = list_create_by(sizeof_type);
    while(l._capacity < length){
        list_expand(&l);
    }
    l.length = length;
    memcpy(l._data, values, sizeof_type * length);
    return l;
}


/**
 * @brief 设置链表的元素
 * @param l 链表
 * @param index 索引
 * @param value 值
 */
void list_set_ptr(list* this, int index, void* value) {
    if( index < 0 || index >= this->length){
        return;
    }
    memcpy(this->_data + index * this->_type_size, value, this->_type_size);
}


/**
 * @brief 获取链表的元素
 * @param l 链表
 * @param index 索引
 * @return void* 返回索引对应的元素
 */
void*list_get_ptr(list* this, int index) {
    if( index < 0 || index >= this->_capacity){
        return NULL;
    }
    return this->_data + index * this->_type_size;
}

void list_append_ptr(list* this, void* value) {
    if( this->length >= this->_capacity){
        list_expand(this);
    }
    memcpy(this->_data + this->length * this->_type_size, value, this->_type_size);
    this->length++;
}


/**
 * @brief 删除链表的元素
 * @param l 链表
 * @param index 索引
 */
void list_erase(list* this, int index) {
    if(index >= this->length || index < 0){
        return;
    }
    memmove(this->_data + index * this->_type_size, this->_data + (index + 1) * this->_type_size, (this->length - index - 1) * this->_type_size);
    this->length--;
}


/**
 * @brief 扩容链表
 * @param l 链表
 */
void list_expand(list* this) {
    if(this->_capacity < 64){
        this->_capacity *= 2;
    } else {
        this->_capacity += 32;
    }
    this->_data = realloc(this->_data, this->_type_size * this->_capacity);
}


/**
 * @brief 释放链表
 * @param l 链表
*/
void list_free(list* this) {
    free(this->_data);
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


map map_init_by(int len, map_pair* data){
    map m = map_create();
    for(int i=0; i<len; i++){
        map_set(&m, data[i].key, data[i].value);
    }
    return m;
}


/**
 * @brief 设置映射的键值对
 * @param d 映射
*/
void map_set(map* this, str key, int value) {
    int is_set = 0;
    for(int i = 0; i < this->_capacity; i++){
        if(is_set == 0 && this->keys[i] == NULL){
            this->keys[i] = malloc(strlen(key) + 1);
            strcpy(this->keys[i], key);
            this->values[i] = value;
            is_set = 1;
            continue;
        }
        if(is_set == 0 && this->keys[i] != NULL && strcmp(this->keys[i], key) == 0 ){
            this->values[i] = value;
            return;
        }
        if(is_set == 1 && this->keys[i] != NULL && strcmp(this->keys[i], key) == 0){
            free(this->keys[i]);
            this->keys[i] = NULL;
            this->values[i] = 0;
            return;
        }
    }
    if(is_set == 0){
        map_expand(this);
        map_set(this, key, value);
    }
}


/**
 * @brief 获取映射的值
 * @param d 映射
 * @param key 键
 * @return int 返回键对应的值
 */
int map_get(map* this, str key) {
    for(int i = 0; i < this->_capacity; i++){
        if(this->keys[i] == NULL){
            continue;
        }
        if(strcmp(this->keys[i], key) == 0){
            return this->values[i];
        }
    }
    return 0;
}


/**
 * @brief 删除映射的键值对
 * @param d 映射
 * @param key 键
 */
void map_remove(map* this, str key) {
    for(int i = 0; i < this->_capacity; i++){
        if(strcmp(this->keys[i], key) == 0){
            free(this->keys[i]);
            this->keys[i] = NULL;
            return;
        }
    }
}


/**
 * @brief 扩容映射
 * @param d 映射
 */
void map_expand(map* this) {
    this->_capacity += 16;
    this->keys = realloc(this->keys, sizeof(str) * this->_capacity);
    for(int i=this->_capacity - 16; i < this->_capacity; i++){
        this->keys[i] = NULL;
    }
    this->values = realloc(this->values, sizeof(int) * this->_capacity);
}


/**
 * @brief 释放映射
 * @param d 映射
*/
void map_free(map* this) {
    for(int i = 0; i < this->_capacity; i++){
        free(this->keys[i]);
    }
    free(this->keys);
    free(this->values);
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


dict dict_init_by(int len, dict_pair* data){
    dict d = dict_create();
    for(int i=0; i<len; i++){
        dict_set(&d, data[i].key, data[i].value);
    }
    return d;
}


/**
 * @brief 设置字典的键值对
 * @param d 字典
 */
void dict_set(dict* this, str key, str value) {
    int is_set = 0;
    for(int i = 0; i < this->_capacity; i++){
        if(is_set == 0 && this->keys[i] == NULL){
            this->keys[i] = malloc(strlen(key) + 1);
            strcpy(this->keys[i], key);
            this->values[i] = malloc(strlen(value) + 1);
            strcpy(this->values[i], value);
            is_set = 1;
            continue;
        }
        if(is_set == 0 && this->keys[i] != NULL && strcmp(this->keys[i], key) == 0 ){
            free(this->values[i]);
            this->values[i] = malloc(strlen(value) + 1);
            strcpy(this->values[i], value);
            return;
        }
        if(is_set == 1 && this->keys[i] != NULL && strcmp(this->keys[i], key) == 0){
            free(this->keys[i]);
            this->keys[i] = NULL;
            free(this->values[i]);
            this->values[i] = NULL;
            return;
        }
    }
    if(is_set == 0){
        dict_expand(this);
        dict_set(this, key, value);
    }
}


/**
 * @brief 获取字典的值
 * @param d 字典
 * @param key 键
 * @return str 返回键对应的值
 */
str dict_get(dict* this, str key) {
    for(int i = 0; i < this->_capacity; i++){
        if(this->keys[i] == NULL){
            continue;
        }
        if(strcmp(this->keys[i], key) == 0){
            return this->values[i];
        }
    }
    return NULL;
}


/**
 * @brief 删除字典的键值对
 * @param d 字典
 * @param key 键
 */
void dict_remove(dict* this, str key) {
    for(int i = 0; i < this->_capacity; i++){
        if(strcmp(this->keys[i], key) == 0){
            free(this->keys[i]);
            this->keys[i] = NULL;
            free(this->values[i]);
            this->values[i] = NULL;
            return;
        }
    }
}


/**
 * @brief 扩容字典
 * @param d 字典
 */
void dict_expand(dict* this) {
    this->_capacity += 16;
    this->keys   = realloc(this->keys, sizeof(str) * this->_capacity);
    this->values = realloc(this->values, sizeof(str) * this->_capacity);
    for(int i=this->_capacity - 16; i < this->_capacity; i++){
        this->keys[i]   = NULL;
        this->values[i] = NULL;
    }
}


/**
 * @brief 释放字典
 * @param d 字典
*/
void dict_free(dict* this) {
    for(int i = 0; i < this->_capacity; i++){
        free(this->keys[i]);
        free(this->values[i]);
    }
    free(this->keys);
    free(this->values);
}


/**
 * @brief 对一个字符串进行复制，同时自带内存回收机制
 * @param s 字符串
 * @return str 返回创建的字符串
 */
str str_static(str s) {
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
    for(; strings[cursor] != NULL;cursor = (cursor + 1) % STRING_EXTRA_LIMIT){
        if(str_use[cursor] <= 1){
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


/**
 * @brief 统一字符串的创建方式
*/
#define string(s) ({_Generic((s),\
    int: ({char _s[256]; sprintf(_s, "%d", s); str_static(_s);}),\
    double: ({char _s[256]; sprintf(_s, "%lf", s); str_static(_s);}),\
    float: ({char _s[256]; sprintf(_s, "%f", s); str_static(_s);}),\
    char*: str_static((char*)(long long)s)\
);})
