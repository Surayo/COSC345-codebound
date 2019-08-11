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
    //char *cwd = NULL;
    char *filetext = NULL, *cleantext = NULL;
    char file_location[50];
    char **story_path = emalloc(sizeof(char*));
    char* currentPosition = NULL;
    FILE *fptr = NULL;
    int path_count = 0;
    
    char cwd[300];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    strcpy(file_location, "/Devolution/[C0].txt");
    
    while (true){
        fptr = openfile(cwd, file_location);
        if (fptr == NULL){
            break;
        }
        filetext = setFile(fptr);
        setBracketPoints(filetext);
        currentPosition = getCurrentFile();
    
        //Add to the current path
        story_path[path_count] = currentPosition;
        path_count ++;
        
        //Set the text
        setStoryText(filetext);
        cleantext = getCleanText();
        printf("%s\n", cleantext);
        
        /* That's how you save the shit
        save_path(cwd, story_path, path_count);
        story_path = open_save(cwd, story_path);
        printf("Reading the savefile: %s\n", story_path[0]);*/
        
        break;
    }
    
    //Freeing memory
    for (int i = 0; i < path_count; i++){
        free(story_path[i]);
    }
    free(story_path);
    free(filetext);
    free(cleantext);
    closefile(fptr);
    freeText();
    
    return 0;
}

