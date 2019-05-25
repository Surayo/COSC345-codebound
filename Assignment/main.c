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
#include "graphics.h"
#include "mylib.h"

int main(int argc, const char * argv[]) {
    char *cwd = NULL;
    char *text = NULL;
    char *choice = NULL, *next_file = NULL;
    FILE *fptr;
    
    cwd = emalloc(150 * sizeof(char));
    
    cwd = current_directory(cwd);
    //fptr is a pointer to the story text
    fptr = openfile(cwd, "/Devolution/C0.txt");
    text = setFile(fptr);
    
    store_brackets(text);
    text = getCleanText();
    printf("%s\n", text);
    
    choice = getChoiceText(1);
    printf("%s\n", choice);
    next_file = getNextFile(1);
    printf("%s\n", next_file);
    
    //create_window();
    closefile(fptr);
    
    free(cwd);
    free(text);
    
    return 0;
}
