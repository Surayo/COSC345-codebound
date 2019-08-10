//  fileManager.c
//  Assignment
//
//  Created by Marcus Anderson on 5/2/19.
//  Copyright © 2019 CodeBound. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fileManager.h"
#include "mylib.h"

char* concat(const char *s1, const char *s2){
    char *result = emalloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    if(result == NULL){
        perror("Error! Can't malloc\n");
        exit(1);
    }else {
        // in real code you would check for errors in malloc here
        strcpy(result, s1);
        strcat(result, s2);
        return result;
    }
}

//Save current story path to a save file
void save_path(char *cwd, char **story, int storyDepth){
    FILE *fp;
    
    cwd = concat(cwd, "/savefile.txt");
    fp = fopen (cwd, "w");
    for (int i = 0; i < storyDepth; i++){
        fprintf(fp, "%s\n", story[i]);
    }
    fclose(fp);
}

//Open the save file
char** open_save(char *cwd, char **story_path){
    FILE *fp;
    const size_t line_size = 50;
    char* line = malloc(line_size);
    int i = 0;
    
    fp = openfile(cwd, "/savefile.txt");
    while (fgets(line, line_size, fp) != NULL) {
        story_path[i] = line;
        i++;
    }
    fclose(fp);
    free(line);
    return story_path;
}

//Get the current directory
char* current_directory(char *cwd){
    if (getcwd(cwd, sizeof(char) * 200) != NULL) {
        return cwd;
    } else {
        perror("getcwd() error");
        return NULL;
    }
}

//Open file
FILE* openfile(char *cwd, char *filename){
    FILE *fptr;
    
    cwd = concat(cwd, filename);
    
    fptr = fopen(cwd,"r");
    if(fptr == NULL){
        perror("Error: cannot find file\n");
        return NULL;
    }
    return fptr;
}

//Close the file
void closefile(FILE *fptr){
    fclose(fptr);
}
