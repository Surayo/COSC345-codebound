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
int choiceNum = 0;

// Gets the cleaned text file
char* getCleanText(){
    return clean_block_text;
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

//Stores the brackets from the text
void store_brackets(char *filetext){
    int i = 0;
    int listIndex = 0;
    
    bool choices = false;
    char *target = NULL, *nextFile = NULL;
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
                target = erealloc(target, bytes);
            } else{
                target = emalloc(bytes);
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
        if (choices == true){
            //Use the same method as above and the pointers should still work,
            //start and end should still be set
            unsigned long len = strlen(target);
            char output[len];
            nextFile = removeFirstAndLast(target, output, len);
            if (choiceNum == 0 && choice1 == NULL){
                choice1 = emalloc(sizeof(choice1));
                choice1->choice_file = emalloc(10 * sizeof(choice1->choice_text[0]));
                strcpy(choice1->choice_file, nextFile);
                choiceNum++;
            }
            else if (choiceNum == 1 && (strcmp(choice1->choice_file, nextFile) != 0)){
                choice2 = emalloc(sizeof(choice2));
                choice2->choice_file = emalloc(10 * sizeof(choice2->choice_text[0]));
                strcpy(choice2->choice_file, nextFile);
                choiceNum++;
            }
            else if (choiceNum == 2 && (strcmp(choice2->choice_file, nextFile) != 0)){
                choice3 = emalloc(sizeof(choice3));
                choice3->choice_file = emalloc(10 * sizeof(choice3->choice_text[0]));
                strcpy(choice3->choice_file, nextFile);
                choiceNum++;
            }
            
        }
        i++;
    } // End while loop
    target = NULL;
    nextFile = NULL;
    
    free(nextFile);
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
