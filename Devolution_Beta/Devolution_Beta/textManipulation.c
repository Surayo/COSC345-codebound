//  textManipulation.c
//  Assignment
//
//  Created by Marcus Anderson on 5/9/19.
//  Copyright © 2019 CodeBound. All rights reserved.

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
struct choice story_choices[3];


char *startIndexes[50];
char *endIndexes[50];
int choiceAmount = 0, bracketAmount = 0;

void freeChoices(){
}

// Gets the cleaned text file
char* getCleanText(){
    return clean_block_text;
}

struct choice getChoice(int num){
    return story_choices[num];
}

// Adds all of the pointers to the array
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
    printf("Brackets: %d\n", bracketAmount);
    printf("Choices: %d\n", choiceAmount);
}

// Get the current file
char* getCurrentFile(){
    if (bracketAmount < 1){
        return NULL;
    }
    long bytes = (((char *)endIndexes[0]) + 1) - ((char *)startIndexes[0]); //3
    char* file = emalloc(bytes * sizeof(char));
    strlcpy(file, startIndexes[0], bytes);
    
    return file;
}

// Will take a character sex input as well as character name
void characterInserts(int endIndex, int startIndex){
    char* inserts[] = {"Xe", "Xer", "Xis", "Xers", "Xself", "Xther", "Xm", "Xoy"};
    char* male[] = {"he", "him", "his", "his", "himself", "brother", "em", "boy"};
    char* female[] = {"she", "her", "her", "hers", "herself", "sister", "er", "girl"};
    
    size_t bytes = ((((char *)endIndexes[endIndex])) - ((char *)startIndexes[startIndex]));
    char* test = emalloc(bytes * sizeof(char));
    strlcpy(test, (startIndexes[startIndex] + 1), bytes);
    //printf("%s\n", test);
    if (strcmp(test, "NAME") == 0){
        strcat(clean_block_text, " Nathorn");
        return;
    }
}

// Set the text blocks
void setStoryText(char *filetext){
    int endIndex = 0, startIndex = 1, checkCount = 0;
    
    while (checkCount < 2){
        size_t bytes = (((char *)startIndexes[startIndex]) - ((char *)endIndexes[endIndex])) - 1;
        char* copyText = emalloc(bytes * sizeof(char));
        strlcpy(copyText, (endIndexes[endIndex] + 1), bytes);
        strcat(clean_block_text, copyText);
        free(copyText);
        
        endIndex++;
        characterInserts(endIndex, startIndex);
        startIndex++;
        char* check = startIndexes[startIndex];
        if (check[1] == 'C'){
            checkCount++;
        }
    }
}

// Set the choices
void setChoices(char* filetext){
    int startIndex = 1, endIndex = 1;
    char* check = startIndexes[startIndex];
    while ((check[1]) != 'C'){
        startIndex++;
        endIndex++;
        check = startIndexes[startIndex];
    }
    
    
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
    
    // Sets the clean block text
    clean_block_text = emalloc(sizeof(filetext) * sizeof(char));
    
    return filetext;
}
