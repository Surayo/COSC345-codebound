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

// Prints out the text file
void fileprint(FILE *file){
    char *filetext;
    long bytes;
    int i = 0, brackets = 0;
    
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
    
    while (filetext[i] != '\0'){
        if (filetext[i] == '['){
            brackets ++;
        }
        i++;
    }
    
    printf("%s\n", filetext);
    printf("\n\nBrackets: %d\n", brackets);
    
    free(filetext);
}
