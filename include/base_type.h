#ifndef __BASE_TYPE_HEADER__
#define __BASE_TYPE_HEADER__

typedef struct{
    int _type_size;
    int length;
    int _capacity;
    void* _data;
} list;

list list_create(int);
void list_setitem(list*, int, void*);
void*list_getitem(list*, int);
void list_append(list*, void*);
void list_expand(list*);

typedef char* str;

#endif