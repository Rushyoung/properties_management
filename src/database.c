//
// Created by rushy on 2024/4/6.
//
#include "../include/database.h"

inline int fp_move(FILE* fp, long offset){
    if(offset < 0 || offset > 16){
        return fseek(fp, offset, SEEK_CUR);
    }
    for(long i = 0; i < offset; i++){
        fgetc(fp);
    }
    return 0;
}


