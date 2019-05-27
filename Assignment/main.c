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
    int choice_num, check;
    
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
        choice = getChoiceText(2);
        printf("%s\n", choice);
        choice = getChoiceText(3);
        printf("%s\n", choice);
        
        printf("Please enter a value between 1 and 3:\n");
        check = scanf("%d", &choice_num);
        if (check != 1){
            printf("scanf returned code %d\n", check);
            return EXIT_FAILURE;
        }
        
        next_file = getNextFile(choice_num);
        //printf("%s\n", next_file);
    
        //file_location = NULL;
        strcpy(file_location, "/Devolution/");
        strcat(file_location, next_file);
        strcat(file_location, ".txt");
        //choice_num = 0;
    
        freeChoices();
        //createWindow(1);
        fclose(fptr);
    }
    
    free(cwd);
    
    return EXIT_SUCCESS;
}

/*
    YOU ARE BREAKING UP THE TEXT FILES LOOK AT ME!!!!!!!!!! REMEMBER
 */
