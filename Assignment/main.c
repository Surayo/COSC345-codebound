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
#include "textManipulation.h"

int main(int argc, const char * argv[]) {
    char *cwd = NULL;
    FILE *fptr;
    
    cwd = malloc(10000 * sizeof(char));
    
    cwd = current_directory(cwd);
    //printf("CWD! %s\n", cwd);
    fptr = openfile(cwd, "/[C1.txt");
    fileprint(fptr);
    closefile(fptr);
    
    free(cwd);
    
    return 0;
}
