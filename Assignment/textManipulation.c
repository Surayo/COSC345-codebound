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

struct choice{
    char *choice_text;
    char *choice_file;
};

char *clean_block_text = NULL;
struct choice choice1;
struct choice choice2;
struct choice choice3;

// Gets the cleaned text file
char* getCleanText(){
    return clean_block_text;
}

void removeBrackets(char *filetext, char *target, char *start, char *end){
    char *storyText = NULL;
    
    if (clean_block_text == NULL){
        clean_block_text = malloc (strlen(filetext) * sizeof(char));
    }
    
    long bytes = ((char *)end) - ((char *)start);
    storyText = malloc(bytes * sizeof(char));
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

//Stores the brackets from the text
void store_brackets(char *filetext){
    int i = 0;
    int listIndex = 0;
    
    bool choices = false;
    char *target = NULL;
    char *start = NULL, *end = NULL;
    char *startLocation = NULL, *endLocation = NULL;
    
    while (filetext[i] != '\0'){
        //printf("Filenum: %c\n", filetext[i]);
        if (filetext[i] == '['){
            start = &filetext[i];
            endLocation = &filetext[i];
        }
        else if (filetext[i] == ']'){
            end = &filetext[i] + 1;
            startLocation = &filetext[i] + 1;
            endLocation = NULL;
            }

        // Adds the bracketed word into a dynamic array
        if (start != NULL && end != NULL){
            target = NULL;
            long bytes = ((char *)end) - ((char *)start);
            if (target != NULL){
                target = realloc(target, bytes);
            } else{
                target = malloc(bytes);
            }
            strncpy (target, start, bytes);

            if (target != NULL){
                if (target[1] == 'C' && choices == false){
                    choices = true;
                }
            }
            start = NULL;
            end = NULL;
            listIndex++;
        }
        
        //Clean body text
        else if (startLocation != NULL && endLocation != NULL && choices == false){
            removeBrackets(filetext, target, startLocation, endLocation);
            startLocation = NULL;
            endLocation = NULL;
        }
        
        
        i++;
    }
    target = NULL;
    free(target);
    free(filetext);
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
