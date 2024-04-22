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


#endif //PROPERTY_AUTH_H
