//
//  main.c
//  Assignment
//
//  Created by Marcus Anderson on 4/4/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fileLoader.h"

int main(int argc, const char * argv[]) {
    char *meh = NULL;
    FILE *fptr;
    
    meh = malloc(10000 * sizeof(char));
    
    meh = current_directory(meh);
    printf("CWD! %s\n", meh);
    fptr = openfile(meh, "/[C1.txt");
    printstuff(fptr);
    
    free(meh);
    
    return 0;
}
