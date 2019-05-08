//
//  fileLoader.h
//  Assignment
//
//  Created by Marcus Anderson on 5/2/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#ifndef fileLoader_h
#define fileLoader_h

extern char* concat(const char *s1, const char *s2);
extern char* current_directory(char *cwd);
extern FILE* openfile(char *cwd, char *filename);
extern void printstuff(FILE *fptr);

#endif /* fileLoader_h */
