//  main.c
//  Devolution_Beta
//
//  Created by Marcus Anderson on 7/17/19.
//  Copyright © 2019 CodeBound. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "fileManager.h"
#include "textManipulation.h"
#include "mylib.h"

int main(int argc, const char * argv[]) {
    char *filetext = NULL, *cleantext = NULL;
    char *choiceText = NULL, *choiceFile = NULL;
    char file_location[100], prefix[] = "/Devolution/[", suffix[] = "].txt";
    FILE *fptr = NULL;
    char cwd[300];
    int choiceNum;

    strcpy(file_location, "/Devolution/[C0].txt");

    while (true){
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("\n");
        } else {
            perror("getcwd() error");
            return 1;
        }
    
        fptr = openfile(cwd, file_location);
        if (fptr == NULL){
            return EXIT_SUCCESS;
        }
        filetext = setFile(fptr);
        setBracketPoints(filetext);
    
        //Set the text
        setStoryText();
        cleantext = getCleanText();
        printf("%s\n", cleantext);
        printf("***************\n");
        setChoices();

        int choiceAmount = getChoiceAmount();
        printf("Choices:\n");
        for (int i = 0; i < choiceAmount; i++){
            choiceText = getChoiceText(i);
            printf("%d: %s", (i + 1), choiceText);
        }
        choiceNum = 0;

        printf("Please enter the corresponding number to make your decision.\n");
        while (1 == scanf("%d", &choiceNum)){
            if (choiceNum <= choiceAmount && choiceNum > 0){
                choiceFile = getChoiceFile(choiceNum - 1);
                break;
            }
        }
        printf("***************\n");
    
        //Setting up next file
        memset(cwd, 0, sizeof(cwd));
        memset(file_location, 0, sizeof(file_location));
        strcpy(file_location, prefix);
        strcat(file_location, choiceFile);
        strcat(file_location, suffix);

        //Freeing memory
        free(filetext);
        free(cleantext);
        closefile(fptr);
        freeAndReset();
        }
    
    return EXIT_SUCCESS;
}




