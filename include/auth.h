//
// Created by 小小喵姬 on 2024/4/20.
//
#include "../include/database.h"
#ifndef PROPERTY_AUTH_H
#define PROPERTY_AUTH_H
/**
 * @return: username error:-1
 * @return: password error:-2
 * */
int login_verify(db* _database, str username, str password);

/**
 * @return:username has existed:-1
 * @return:no error: 0
 * */
int add_user(db* _database, str username, str password, str auth);

int add_guard(db* _database, str username, str password, str name, str region, str time);

int add_residents(db* _database, str username, str password, str name, str region, str room);

int add_cleaner(db* _database, str username, str password, str name, str region, str time);

int update_password(db* _database, str username, str new_password);



#endif //PROPERTY_AUTH_H
