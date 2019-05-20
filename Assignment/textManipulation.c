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

//Removes the brackets from the text
char* remove_brackets(char *filetext){
    int i = 0, brackets = 0;
    
    char *target = NULL;
    char *start, *end;
    
    while (filetext[i] != '\0'){
        printf("Filenum: %c\n", filetext[i]);
        //brackets = strcmp(filetext[i], '[');
        if (filetext[i] == '['){
            start = &filetext[i];
            printf("Start: %ptr\n", start);
            /*if (end = strstr(start, BRACKET2)){
                target = (char *)malloc(end - start + 1);
                memcpy(target, start, end - start);
                target[end - start] = '\0';
            }*/
        }
        i++;
        if (target){
           printf("%s\n", target);
        }
        free(target);
    }
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
    
    filetext = remove_brackets(filetext);
    
    printf("%s\n", filetext);
    //printf("\n\nBrackets: %d\n", brackets);
    
    free(filetext);
}
