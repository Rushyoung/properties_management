#ifndef DEBUG
#include "user.h"
#endif

#include<string.h>

auth auth_create(const str name, const str word){
    auth result;
    strcpy(result.username, name);
    strcpy(result.password, word);
    return result;
}


int auth_check(const auth* this)
