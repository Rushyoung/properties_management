#ifndef DEBUG
#include "user.h"
#endif

#include<stdio.h>
#include<string.h>

auth auth_create(const str name, const str word){
    auth result;
    strcpy(result.username, name);
    strcpy(result.password, word);
    return result;
}


bool auth_is_login(const auth* this){
    ;
}

user user_create(const str username, const str password, const str phone, const str range){
    user result;
    result.user_auth = auth_create(username, password);
    strcpy(result.phone, phone);
    strcpy(result.zone,  range);
    return result;
}


user user_set_auth(const user* this, const int level){
    ;
}

bool zone_is_contain(const str zone, const int goal){
    char temp_str[32] = {};
    int temp_int = 0, str_idx = 0;
    int range_start = 0, range_end = 0;
    bool is_range = false;
    for(int i=0; zone[i]; i++, str_idx = 0){
        for(; zone[i] && zone[i] != '-' && zone[i] != ','; i++, str_idx++){
            temp_str[str_idx] = zone[i];
        }
        temp_str[str_idx] = 0;
        sscanf(temp_str, "%d", &temp_int);
        if(temp_int == goal){
            return true;
        }
        iif(zone[i] == '-'){
            range_start = temp_int;
            is_range = true;
            continue;
        }
        if(is_range){
            range_end = temp_int;
            for(int in_range = range_start; in_range <= range_end; in_range++){
                if(in_range == goal){
                    return true;
                }
            }
            is_range = false;
            continue;
        }
        if(zone[i] == 0){
            break;
        }
    }
    return false;
}
