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
    for(int i = 0; i < choiceAmount; i++){
        free(story_choices[i].choice_file);
        free(story_choices[i].choice_text);
    }
}

// Gets the cleaned text file
char* getCleanText(){
    return clean_block_text;
}

//Gets a specified choice text
char* getChoiceText(int num){
    return story_choices[num].choice_text;
}

//Gets next file
char* getChoiceFile(int num){
    return story_choices[num].choice_file;
}

// Adds all of the pointers to the array
void setBracketPoints(char *filetext){
    int currentIndex = 0;
    int filelength = strlen(filetext);
    int storeIndex = 0;
    
    while ((filetext[currentIndex]) != '\0' && currentIndex < (filelength - 1)){
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
    strncpy(file, startIndexes[0], bytes);
    
    return file;
}

// Will take a character sex input as well as character name
void characterInserts(int endIndex, int startIndex){
    /*char* inserts[] = {"Xe", "Xer", "Xis", "Xers", "Xself", "Xther", "Xm", "Xoy"};
    char* male[] = {"he", "him", "his", "his", "himself", "brother", "em", "boy"};
    char* female[] = {"she", "her", "her", "hers", "herself", "sister", "er", "girl"};*/
    char name[] = "Nathorn";

    size_t bytes = ((((char *)endIndexes[endIndex])) - ((char *)startIndexes[startIndex]));
    char* test = ecalloc(bytes + 1, sizeof(char));
    strncpy(test, (startIndexes[startIndex] + 1), bytes);
    
    if (strcmp(test, "NAME]") == 0){
        clean_block_text = erealloc(clean_block_text, (strlen(clean_block_text) * strlen(name)));
        strncat(clean_block_text, name, strlen(name));
    }
    free(test);
}

// Set the text blocks
void setStoryText(char *filetext){
    int endIndex = 0, startIndex = 1, checkCount = 0;
    char* copyText = NULL;
    
    while (checkCount < 2){
        size_t bytes = (((char *)startIndexes[startIndex]) - ((char *)endIndexes[endIndex])) - 1;
        copyText = ecalloc(bytes, sizeof(char));
        strncpy(copyText, (endIndexes[endIndex] + 1), bytes);
        strncat(clean_block_text, copyText, bytes);
        
        endIndex++;
        characterInserts(endIndex, startIndex);
        startIndex++;
        char* check = startIndexes[startIndex];
        if (check[1] == 'C'){
            checkCount++;
        }
        free(copyText);
        copyText = NULL;
    }
}

// Set the choices
void setChoices(char* filetext){
    int startIndex = 1, endIndex = 1, num = 0;
    char* check = startIndexes[startIndex];
    char *nextFile = NULL, *choiceText = NULL;
    
    while ((check[1]) != 'C'){
        startIndex++;
        endIndex++;
        check = startIndexes[startIndex];
    }
    while(num < choiceAmount){
        size_t bytes = (((char *)endIndexes[endIndex]) - ((char *)startIndexes[startIndex]));
        nextFile = ecalloc(bytes, sizeof(char));
        strncpy(nextFile, (startIndexes[startIndex] + 1), bytes - 1);

        startIndex++;

        size_t bytes2 = (((char *)startIndexes[startIndex]) - ((char *)endIndexes[endIndex]));
        choiceText = ecalloc(bytes2, sizeof(char));
        strncpy(choiceText, (endIndexes[endIndex] + 1), bytes2 - 1);

        endIndex++;

        story_choices[num].choice_file = nextFile;
        story_choices[num].choice_text = choiceText;
        num++;
    }
}

// Sets the file into a string
char* setFile(FILE *file){
    char *filetext = NULL;
    long bytes = 0;
    
    // Number of bytes in file
    fseek(file, 0L, SEEK_END);
    bytes = ftell(file);
    
    // Set to beginning of the file
    fseek(file, 0L, SEEK_SET);
    
    // Allocate memory for the entire file
    filetext = (char*)ecalloc(bytes, sizeof(char));
    if (filetext == NULL){
        perror("Error! Allocating memory\n");
        exit(1);
    }
    
    // Copy text of file into filetext and prints text
    fread(filetext, sizeof(char), bytes-1, file);
    
    // Sets the clean block text
    clean_block_text = ecalloc(strlen(filetext), sizeof(filetext[0]));
    
    return filetext;
}
