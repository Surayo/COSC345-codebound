//
//  textManipulation.c
//  Assignment
//
//  Created by Marcus Anderson on 5/9/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "textManipulation.h"
#include "mylib.h"

struct choice{
    char *choice_text;
    char *choice_file;
};

char *clean_block_text = NULL;
struct choice* choice1;
struct choice* choice2;
struct choice* choice3;

char *startIndexes[50];
char *endIndexes[50];
int choiceAmount = 0, bracketAmount = 0;

void freeChoices(){
}

// Gets the cleaned text file
char* getCleanText(){
    return clean_block_text;
}

struct choice* getChoice(int num){
    if (num == 1){
        return choice1;
    } else if (num == 2){
        return choice2;
    } else if (num == 3){
        return choice3;
    } else{
        return NULL;
    }
}

/* Adds all of the pointers to the array
 */
void setBracketPoints(char *filetext){
    int currentIndex = 0;
    int storeIndex = 0;
    
    while (filetext[currentIndex] != '\0'){
        if (filetext[currentIndex] == '['){
            startIndexes[storeIndex] = &filetext[currentIndex];
            bracketAmount ++;
            if (filetext[currentIndex + 1] == 'C'){
                choiceAmount ++;
            }
        } else if (filetext[currentIndex] == ']'){
            endIndexes[storeIndex] = &filetext[currentIndex];
            storeIndex++;
        }
        
        currentIndex++;
    }
    printf("Test1: %c\n", *startIndexes[1]);
    printf("Test2: %c\n", *endIndexes[2]);
    printf("Brackets: %d\n", bracketAmount);
    printf("Choices: %d\n", choiceAmount);
}

/*Get the current file
 */
char* currentFile(){
    if (bracketAmount < 1){
        return NULL;
    }
    long bytes = (((char *)endIndexes[0]) + 1) - ((char *)startIndexes[0]); //3
    printf("Num: %ld\n", bytes);
    char* file = emalloc(bytes * sizeof(char));
    printf("Size of filepiece: %ld\n", sizeof(file));
    strncpy(file, startIndexes[0], bytes);
    
    return file;
}


// Sets the file into a string
char* setFile(FILE *file){
    char *filetext;
    long bytes;
    
    // Number of bytes in file
    fseek(file, 0L, SEEK_END);
    bytes = ftell(file);
    
    // Set to beginning of the file
    fseek(file, 0L, SEEK_SET);
    
    // Allocate memory for the entire file
    filetext = (char*)calloc(bytes, sizeof(char));
    if (filetext == NULL){
        perror("Error! Allocating memory\n");
        exit(1);
    }
    
    // Copy text of file into filetext and prints text
    fread(filetext, sizeof(char), bytes, file);
    
    return filetext;
}
