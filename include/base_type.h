#ifndef __BASE_TYPE_HEADER__
#define __BASE_TYPE_HEADER__

typedef struct{
    int _type_size;
    int length;
    int _capacity;
    void* _data;
} list;

list list_create_by(int);
void list_set_ptr(list*, int, void*);
void*list_get_ptr(list*, int);
void list_append_ptr(list*, void*);
void list_expand(list*);
void list_free(list*);
#define list_create(type) ({list_create_by(sizeof(type));})
#define list_get(type, l, index) ({*(type*)list_get_ptr((l), (index));})
#define list_set(l, index, value) ({typeof(value) _v=value; list_set_ptr((l), (index), &_v);})
#define list_append(l, value) ({typeof(value) _v=(value); list_append_ptr((l), &_v);})

typedef char* str;

typedef struct{
    int _capacity;
    str *keys;
    int *values;
} map;

map map_create();
void map_set(map*, str, int);
int  map_get(map*, str);
void map_remove(map*, str);
void map_expand(map*);
void map_free(map*);

typedef struct{
    int _capacity;
    str *keys;
    str *values;
} dict;

dict dict_create();
void dict_set(dict*, str, str);
str  dict_get(dict*, str);
void dict_remove(dict*, str);
void dict_expand(dict*);
void dict_free(dict*);

#define STRING_EXTRA_LIMIT 128
str string(str);

#endif
