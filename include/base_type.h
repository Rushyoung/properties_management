#ifndef __BASE_TYPE_HEADER__
#define __BASE_TYPE_HEADER__

typedef int bool;
#define true  1
#define false 0

typedef struct{
    int _type_size;
    int length;
    int _capacity;
    void* _data;
} list;

list list_create_by(int);
list list_init_by(int, int, void*);
void list_set_ptr(list*, int, void*);
void*list_get_ptr(list*, int);
void list_append_ptr(list*, void*);
void list_erase(list*, int);
void list_expand(list*);
void list_sort(list*, int(*)(const void*, const void*));
void list_reverse(list*);
void list_free(list*);
#define list_create(type) ({list_create_by(sizeof(type));})
#define list_init(values, ...) ({typeof(values) _l[]={values, ##__VA_ARGS__}; list_init_by(sizeof(values), sizeof(_l)/sizeof(values), _l);})
#define list_get(type, l, index) ({*(type*)list_get_ptr((l), (index));})
#define list_set(l, index, value) ({typeof(value) _v=value; list_set_ptr((l), (index), &_v);})
#define list_append(l, value) ({typeof(value) _v=(value); list_append_ptr((l), &_v);})
#define list_find(l, goal) ({int _i=-1;for(int i=0; i<(l)->length; i++)if(list_get(typeof(goal), l, i)==goal){_i=i; break;}_i;})

typedef char* str;

typedef struct{
    str key;
    int value;
} map_pair;
typedef struct{
    int _capacity;
    str *keys;
    int *values;
} map;

map  map_create();
map  map_init_by(int, map_pair*);
void map_set(map*, str, int);
int  map_get(map*, str);
void map_remove(map*, str);
void map_expand(map*);
void map_free(map*);
#define map_init(...) ({map_pair _m[]={__VA_ARGS__}; map_init_by(sizeof(_m)/sizeof(map_pair), _m);})

typedef struct{
    str key;
    str value;
} dict_pair;
typedef struct{
    int _capacity;
    str *keys;
    str *values;
} dict;

dict dict_create();
dict dict_init_by(int, dict_pair*);
void dict_set(dict*, str, str);
str  dict_get(dict*, str);
void dict_remove(dict*, str);
void dict_expand(dict*);
void dict_free(dict*);
#define dict_init(...) ({dict_pair _d[]={__VA_ARGS__}; dict_init_by(sizeof(_d)/sizeof(dict_pair), _d);})

#define STRING_EXTRA_LIMIT 128
#define STRING_SHORT_STD   8
str str_static(str);
#define string(s) ({_Generic((s),\
    int: ({char _s[256]; sprintf(_s, "%d", s); str_static(_s);}),\
    double: ({char _s[256]; sprintf(_s, "%lf", s); str_static(_s);}),\
    float: ({char _s[256]; sprintf(_s, "%f", s); str_static(_s);}),\
    char*: str_static((char*)(long long)s)\
);})

int sort_as_int(const void*, const void*);
int sort_as_str(const void*, const void*);
int sort_as_double(const void*, const void*);

#endif
