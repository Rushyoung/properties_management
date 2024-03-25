
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
list list_create(int sizeof_type) {
    list l;
    l._type_size = sizeof_type;
    l.length = 0;
    l._capacity = 8;
    l._data = malloc(sizeof_type * l._capacity);
    return l;
}


/**
 */
void list_setitem(list* l, int index, void* value) {
    if( index < 0 || index >= l->_capacity * 2){
        return;
    }
    if( index >= l->_capacity && index < l->_capacity * 2){
        list_expand(l);
    }
    memcpy(l->_data + index * l->_type_size, value, l->_type_size);
}

void*list_getitem(list* l, int index) {
    if( index < 0 || index >= l->_capacity){
        return (void*)(0);
    }
    return l->_data + index * l->_type_size;
}

void list_append(list* l, void* value) {
    if( l->length >= l->_capacity){
        list_expand(l);
    }
    memcpy(l->_data + l->length * l->_type_size, value, l->_type_size);
    l->length++;
}

void list_expand(list* l) {
    if(l->_capacity < 64){
        l->_capacity *= 2;
    } else {
        l->_capacity += 32;
    }
    l->_data = realloc(l->_data, l->_type_size * l->_capacity);
}