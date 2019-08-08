//  main.c
//  Devolution_Beta
//
//  Created by Marcus Anderson on 7/17/19.
//  Copyright © 2019 CodeBound. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fileManager.h"
#include "textManipulation.h"
#include "mylib.h"

int main(int argc, const char * argv[]) {
    char *cwd = NULL;
    char *text = NULL;
    char file_location[50];
    char **story_path = emalloc(sizeof(char*));
    FILE *fptr;
    int path_count = 0;
    
    cwd = emalloc(150 * sizeof(char));
    
    cwd = current_directory(cwd);
    strcpy(file_location, "/Devolution/[C0].txt");
    
    while (true){
        fptr = openfile(cwd, file_location);
        if (fptr == NULL){
            break;
        }
        text = setFile(fptr);
        setBracketPoints(text);
        char* currentPosition = getCurrentFile();
    
        //Add to the current path
        story_path[path_count] = currentPosition;
        path_count ++;
        
        //Set the text
        setStoryText(text);
        
        /* That's how you save the shit
        save_path(cwd, story_path, path_count);
        story_path = open_save(cwd, story_path);
        printf("Reading the savefile: %s\n", story_path[0]);*/
        
        break;
    }
    free(story_path);
    return 0;
}
