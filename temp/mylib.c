//  mylib.c
//  Assignment
//
//  Created by Marcus Anderson on 5/24/19.
//  Copyright © 2019 CodeBound. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

void *emalloc(size_t s){
    void *result = malloc(s);
    if (NULL == result){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s){
    void *result = realloc(p, s);
    if(NULL == result){
        fprintf(stderr, "memory reallocation failed. \n");
        exit(EXIT_FAILURE);
    }
    return result;
}
