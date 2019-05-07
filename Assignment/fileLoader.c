//
//  fileLoader.c
//  Assignment
//
//  Created by Marcus Anderson on 5/2/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fileLoader.h"

char c [1000];
FILE *fptr;

char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

//Get the current directory
char* current_directory(char *cwd){
    printf("Check 1\n");
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Check 2\n");
        printf("Current working dir: %s\n", cwd);
    } else {
        printf("Check 3\n");
        perror("getcwd() error");
        //return NULL;
    }
    printf("Check 4\n");
    return cwd;
}

//Move string back to ../assignment
void fix_url(char *cwd){
    unsigned long len = strlen(cwd);
    char *story_dir = strstr(cwd, "Build");
    if(story_dir != NULL){
        *story_dir = '\0';
        strcat(cwd, story_dir+len);
        printf("%s\n", cwd);
    }
}

//Open file
void openfile(char *cwd){
    char* url = concat(cwd, "/Devolution/[C0] meeting Vagabonds.txt");
    fptr = fopen(url,"r");
    printf("%s\n", url);
    if(fptr == NULL){
        printf("Error! Opening file\n");
        exit(1);
    }
}

/*// reads text until newline
void printstuff(){
    fscanf(fptr,"%[^\n]", c);
    printf("%s\n", c);
}

void free(){
    fclose(fptr);
    //free(url);
}*/
