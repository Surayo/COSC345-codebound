//
//  main.c
//  Assignment
//
//  Created by Marcus Anderson on 4/4/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, const char * argv[]) {
    char c [1000];
    char cwd [100];
    FILE *fptr;
    
    //Get the current directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    
    //Move string back to ../assignment
    unsigned long len = strlen(cwd);
    char *story_dir = strstr(cwd, "Build");
    if(story_dir != NULL){
        *story_dir = '\0';
        strcat(cwd, story_dir+len);
        printf("%s\n", cwd);
    }
    
    //Open file
    char* url = concat(cwd, "Assignment/Act1/[Choice1.1].txt");
    fptr = fopen(url,"r");
    if(fptr == NULL){
        printf("Error! Opening file\n");
        exit(1);
    }
    
    // reads text until newline
    fscanf(fptr,"%[^\n]", c);
    printf("%s\n", c);
    
    fclose(fptr);
    return 0;
}
