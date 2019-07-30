//
//  main.c
//  Devolution_Beta
//
//  Created by Marcus Anderson on 7/17/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fileLoader.h"
#include "textManipulation.h"
#include "mylib.h"

int main(int argc, const char * argv[]) {
    char *cwd = NULL;
    char file_location[50];
    FILE *fptr;
    
    cwd = emalloc(150 * sizeof(char));
    //file_location = emalloc(50 * sizeof(char));
    
    cwd = current_directory(cwd);
    strcpy(file_location, "/Devolution/C0.txt");
    //fptr is a pointer to the story text
    
    while (true){
        fptr = openfile(cwd, file_location);
        if (fptr == NULL){
            break;
        }
        
    }
    
    return 0;
}
