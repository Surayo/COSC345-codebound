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

char *cleantext = NULL;
char *choice1 = NULL;
char *choice2 = NULL;
char *choice3 = NULL;

void removeBrackets(char *filetext, char *start, char *end){
    char *meh = NULL;
    
    if (cleantext == NULL){
        cleantext = malloc (strlen(filetext) * sizeof(char));
    }
    //printf("End2: %ptr\n", end);
    if (end == NULL){
        end = &filetext[0];
    }
    //printf("Check: %s\n", (end));
    
    ptrdiff_t bytes = ((char *)end) - ((char *)start);
    meh = malloc(bytes * sizeof(char));
    
    strncpy(meh, end, bytes);
    //printf("Test: %s\n", target);
    strcat(cleantext, meh);
    
    //printf("Test1: %s\n", meh);
    meh = NULL;
    free(meh);
    
}

// Gets the cleaned text file
char* getCleanText(){
    return cleantext;
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
    //int bracketnum = getBracketAmount(filetext);
    //char* bracketlist[bracketnum];
    
    bool check = true;
    char *target = NULL;
    char *start = NULL, *end = NULL;
    char *startLocation = NULL, *endLocation = NULL;
    
    while (filetext[i] != '\0'){
        //printf("Filenum: %c\n", filetext[i]);
        if (filetext[i] == '['){
            start = &filetext[i];
            startLocation = &filetext[i];
            printf("Start location: %ptf\n", &start);
        }
        else if (filetext[i] == ']'){
            end = &filetext[i] + 1;
            endLocation = &filetext[i];
            printf("End location: %ptf\n", &end);
            }

        // Adds the bracketed word into a dynamic array
        if (start != NULL && end != NULL){
            ptrdiff_t bytes = ((char *)end) - ((char *)start);
            printf("Bytes: %d\n", bytes);
            target = malloc(bytes);
            strncpy (target, start, bytes);

            printf("Target: %s\n", target);
            /*bracketlist[listIndex] = malloc((strlen(target) + 1) * sizeof bracketlist[0][0]);
            strcpy(bracketlist[listIndex], target);
            printf("ListTarget: %s\n", bracketlist[listIndex]);*/
            if (target[1] == 'C' && check == true){
                printf("Target at 1: %c\n", target[1]);
                check = false;
            }
            if (startLocation != NULL && check == true){
                removeBrackets(filetext, startLocation, endLocation);
                startLocation = NULL;
            }
            
            start = NULL;
            end = NULL;
            listIndex++;
            target = NULL;
            free(target);
        }
        i++;
    }
    /*for (int i = 0; i < bracketnum; i++){
        free(bracketlist[i]);
    }
    free(bracketlist);*/
    free(filetext);
    //return filetext;
}

// Prints out the text file
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
    //filetext = store_brackets(filetext);
    
    //printf("%s\n", filetext);
    //printf("\n\nBrackets: %d\n", brackets);
    
    //free(filetext);
}
