#ifndef __USER_HEADER__
#define __USER_HEADER__

#include "base_type.h"

typedef struct{
    char username[16];
    char password[16];
} auth;

auth auth_create(const str, const str);
bool auth_is_login(const auth*);

typedef struct{ 
    char phone[16];
    auth user_auth;
    char zone[16];
    short int work;
} user;

user user_create(const str, const str, const str, const str);
user user_set_auth(const user*, const int);
bool zone_is_contain(const str, const int);

#endif
