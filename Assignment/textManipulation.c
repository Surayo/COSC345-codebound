//
//  textManipulation.c
//  Assignment
//
//  Created by Marcus Anderson on 5/9/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "textManipulation.h"

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
char* store_brackets(char *filetext){
    int i = 0;
    int listIndex = 0;
    int bracketnum = getBracketAmount(filetext);
    char* bracketlist[bracketnum];
    
    char *target = NULL;
    char *start = NULL, *end = NULL;
    
    while (filetext[i] != '\0'){
        //printf("Filenum: %c\n", filetext[i]);
        if (filetext[i] == '['){
            start = &filetext[i];
            //printf("Start: %ptr\n", start);
        }
        else if (filetext[i] == ']'){
            end = &filetext[i] + 1;
            //printf("End: %ptr\n", end);
            }
        // Adds the bracketed word into a dynamic array
        if (start != NULL && end != NULL){
            ptrdiff_t bytes = ((char *)end) - ((char *)start);
            target = malloc(bytes * sizeof(char));
            strncpy (target, start, bytes);
            printf("Target: %s\n", target);
            bracketlist[listIndex] = malloc((strlen(target) + 1) * sizeof bracketlist[0][0]);
            strcpy(bracketlist[listIndex], target);
            printf("ListTarget: %s\n", bracketlist[listIndex]);
            start = NULL;
            end = NULL;
            listIndex++;
        }
        i++;
    }
    //free(bracketlist);
    return filetext;
}

// Prints out the text file
void fileprint(FILE *file){
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
    
    filetext = store_brackets(filetext);
    
    printf("%s\n", filetext);
    //printf("\n\nBrackets: %d\n", brackets);
    
    free(filetext);
}
