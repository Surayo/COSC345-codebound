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
    
    strcpy(file_location, "/Devolution/[C0].txt");
    
    while (true){
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current working dir: %s\n", cwd);
        } else {
            perror("getcwd() error");
            return 1;
        }
        
        fptr = openfile(cwd, file_location);
        if (fptr == NULL){
            break;
        }
        filetext = setFile(fptr);
        setBracketPoints(filetext);
        
        //Set the text
        setStoryText();
        cleantext = getCleanText();
        printf("%s\n", cleantext);
        setChoices();
        
        /* That's how you save the shit
           save_path(cwd, story_path, path_count);*/
        /*story_path = open_save(cwd, story_path);
          printf("Reading the savefile: %s\n", story_path[0]);*/

        choiceText = getChoiceText(0);
        choiceFile = getChoiceFile(0);
        printf("Test1: %s\n", choiceFile);
        printf("Test2: %s\n", choiceText);

        //Setting up next file
        memset(cwd, 0, sizeof(cwd));
        memset(file_location, 0, sizeof(file_location));
        printf("%s\n", file_location);
        strcpy(file_location, prefix);
        strcat(file_location, choiceFile);
        strcat(file_location, suffix);


        //Freeing memory
        free(filetext);
        free(cleantext);
        closefile(fptr);
        freeAndReset();
        //break;
    }
    
    return 0;
}




