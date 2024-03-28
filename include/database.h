#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "base_type.h"
#include <stdio.h>

int fmove(FILE*, long);

typedef struct{
    char _file_name[256];
    map  _master;
} db;

db   db_connect(const str);

void db_insert_table(db*, const str, const map);
void db_insert_lin(db*, const str, const list);

void db_remove_table(db*, const str);
void db_remove_lin(db*, const str, const int);

str  db_select(db*, const str, const str, const int);
dict db_select_lin(db*, const str, const int);
list db_select_col(db*, const str, const str);

void db_update(db*, const str, const str, const int);
void db_update_lin(db*, const str, const int);

void db_vacuum(db*);

static int _table_skip_to_next(FILE*);
static int _table_skip_to_table(FILE*, const str);

#endif
