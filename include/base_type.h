#ifndef __BASE_TYPE_HEADER__
#define __BASE_TYPE_HEADER__

typedef struct{
    int _type_size;
    int length;
    int _capacity;
    int _is_need_free;
    void* _data;
} list;

list list_create(int);
void list_set(list*, int, void*);
void*list_get(list*, int);
void list_append(list*, void*);
void list_expand(list*);

typedef char* str;

typedef struct{
    int _capacity;
    str *keys;
    int *values;
    int _is_need_free;
} map;

map map_create();
void map_set(map*, str, int);
int  map_get(map*, str);
void map_remove(map*, str);
void map_expand(map*);


typedef struct{
    int _capacity;
    str *keys;
    str *values;
    int _is_need_free;
} dict;

dict dict_create();
void dict_set(dict*, str, str);
str  dict_get(dict*, str);
void dict_remove(dict*, str);
void dict_expand(dict*);

str string(str);

#endif