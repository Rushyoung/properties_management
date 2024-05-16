//
// Created by rushy on 2024/4/6.
//
#include "../include/base_type.h"
#include <stdio.h>
#include <string.h>

#ifndef PROPERTY_DATABASE_H

int fp_move(FILE*, long);
int file_insert(FILE*, const char*);

typedef struct{
    int head;
    int start;
    int column_count;
    int line_width;
    char table_name[256];
} table_info;

table_info table_info_get(FILE*);



typedef struct{
    char file_name[256];
    map master;
} db;
/*
 * @brief:连接数据库
 * @_file_name:连接的数据库文件名
 * @return:返回打开后的db结构体
 * */
db database_connect(const char* _file_name);


/*
 * @brief:向数据库中插入新表信息
 * @_table:表名
 * @_column:表格的列信息
 * @return  如果表名重复则直接返回
 */
void database_insert_table(db* _db, str _table, map _column);


/* @brief:向已有的一张表添加数据（一行）
 * @_table:表名
 * @values:插入的一行
 */
void database_insert_line(db* _db, str _table, list values);
void database_remove_table(db* _db, str _table);
void database_remove_line(db* _db, str _table, int line_no);
/*
 * @brief:根据，表名，列名，行号来查询该位置的数据
 * @_db:打开后的数据库
 * @_table:表名
 * @_column:列名
 * @line_no:行号
 * @return:返回一个字符数组
 * */
str database_select(db* _db, str _table, str _column, int line_no);
list database_select_column(db* _db, str _table, str _column);
dict database_select_line(db* _db, str _table, int line_no);
/*
 * @brief:根据，表名，列名，行号来更新该位置的数据
 * @_db:打开后的数据库
 * @_table:表名
 * @_column:列名
 * @line_no:行号
 * @return:返回一个字符数组
 * */
void database_update(db* _db, str _table, str _column, int line_no, str value);
void database_update_line(db* _db, str _table, int line_no, list _value);

void database_vacuum(db* _db);
/*
 * @brief:数据库备份和回复相关，备份会保存在父目录，命名为restore.db
 * @_database:打开的数据库
 * @return:异常值为-1
 * */
int database_backup(db* _database);
int database_restore(db* _database);

void copy_file(const char *src, const char *dst);


int count_line(FILE* fp);

int skip_to_next_table(FILE*);
int jump_to_table(FILE *_fp, str _table);
int jump_to_position(FILE*, int, int);

/*
 * @brief:初始化数据库
 * @return：返回一个打开的db
 * */
db init();



#define PROPERTY_DATABASE_H

#endif //PROPERTY_DATABASE_H
