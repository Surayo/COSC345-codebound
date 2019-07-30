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
int choiceNum = 0, choiceTextNum = 0;
char *startIndexes[20];
char *endIndexes[20];

void freeChoices(){
    choice1->choice_file = NULL;
    choice1->choice_text = NULL;
    free(choice1->choice_file);
    free(choice1->choice_text);
    choice1 = NULL;
    free(choice1);
    
    choice2->choice_file = NULL;
    choice2->choice_text = NULL;
    free(choice2->choice_file);
    free(choice2->choice_text);
    choice2 = NULL;
    free(choice2);
    
    choice3->choice_file = NULL;
    choice3->choice_text = NULL;
    free(choice3->choice_file);
    free(choice3->choice_text);
    choice3 = NULL;
    free(choice3);
    
    choiceNum = 0;
    choiceTextNum = 0;
    clean_block_text = NULL;
    free(clean_block_text);
}

// Gets the cleaned text file
char* getCleanText(){
    return clean_block_text;
}

char* getNextFile(int num){
    if (num == 1){
        return choice1->choice_file;
    } else if (num == 2){
        return choice2->choice_file;
    } else if (num == 3){
        return choice3->choice_file;
    } else{
        return NULL;
    }
}

char* getChoiceText(int num){
    if (num == 1){
        return choice1->choice_text;
    } else if (num == 2){
        return choice2->choice_text;
    } else if (num == 3){
        return choice3->choice_text;
    } else{
        return NULL;
    }
}

char* removeFirstAndLast(char *file_choice, char *output, unsigned long len){
    if (len > 0){
        strcpy(output, ++file_choice);
    }
    if (len > 1){
        output[len - 2] = '\0';
    }
    return output;
}

void removeBrackets(char *filetext, char *target, char *start, char *end){
    char *storyText = NULL;
    if (clean_block_text == NULL){
        clean_block_text = emalloc (strlen(filetext) * sizeof(char));
    }
    
    long bytes = ((char *)end) - ((char *)start);
    storyText = emalloc(bytes * sizeof(char));
    strncpy(storyText, start, bytes);
    
    if (strcmp(target, "[NAME]") == 0){
        strcat(clean_block_text, "Greg");
    }
    
    strcat(clean_block_text, storyText);
    
    storyText = NULL;
    free(storyText);
}

int getBracketAmount(char *filetext){
    int amount = 0;
    int i = 0;
    while (filetext[i] != '\0'){
        if(filetext[i] == '['){
            amount += 1;
        }
        i ++;
    }
    return amount;
}

// Adds all of the pointers to the array
void setBracketPoints(char *filetext){
    int currentIndex = 0;
    int storeIndex = 0;
    
    while (filetext[currentIndex] != '\0'){
        if (filetext[currentIndex] == '['){
            startIndexes[storeIndex] = &filetext[currentIndex];
        } else if (filetext[currentIndex] == ']'){
            endIndexes[storeIndex] = &filetext[currentIndex];
            storeIndex++;
        }
        
        currentIndex++;
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
    
    return filetext;
}
