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
#include <stdbool.h>
#include "fileLoader.h"
#include "textManipulation.h"
#include "graphics.h"
#include "mylib.h"

int main(int argc, const char * argv[]) {
    char *cwd = NULL;
    char file_location[50];
    char *text = NULL;
    char *choice = NULL, *next_file = NULL;
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
        
        text = setFile(fptr);

        store_brackets(text);
        text = getCleanText();
        printf("%s\n", text);
        
        choice = getChoiceText(1);
        printf("%s\n", choice);
        next_file = getNextFile(1);
        printf("%s\n", next_file);
    
        //file_location = NULL;
        strcpy(file_location, "/Devolution/");
        strcat(file_location, next_file);
        strcat(file_location, ".txt");
    
        freeChoices();
        //create_window();
        fclose(fptr);
    }
    
    free(cwd);
    
    return 0;
}
