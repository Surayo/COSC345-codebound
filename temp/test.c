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

int main() {
    char name[20];
    
    printf("Enter a name fuckface\n");
    while (1 == (scanf("%s", name))){
        printf("Name: %s\n", name);
        
    }
    
    
    return EXIT_SUCCESS;
}




