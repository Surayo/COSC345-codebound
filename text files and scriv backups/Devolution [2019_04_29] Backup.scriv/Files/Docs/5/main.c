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
#include "fileLoader.h"

int main(int argc, const char * argv[]) {
    char *meh = NULL;
    meh = malloc(100 * sizeof meh[0]);
    
    //meh = current_directory(meh);
    //printf("Hebo! %s\n", meh);
    
    
    
    free(meh);
    
    return 0;
}
