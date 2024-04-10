#ifndef __USER_HEADER__
#define __USER_HEADER__

typeof struct{
    char username[16];
    char password[16];
} auth;

auth auth_create(const str, const str);
int auth_check(const auth*);

typeof struct{
    char username[16];
    char phone[16];
    auth user_auth;
    char zone[16];
    short int work;
} user;

user user_create(const str, const str, const str, const str, const short int);


#endif
