//
//  fileManager.h
//  Assignment
//
//  Created by Marcus Anderson on 5/2/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#ifndef fileManager_h
#define fileManager_h

extern char* concat(const char *s1, const char *s2);
extern char* current_directory(char *cwd);
extern FILE* openfile(char *cwd, char *filename);
extern void closefile(FILE *fptr);
extern void save_path(char *cwd, char **story, int storyDepth);
extern char** open_save(char *cwd, char **story_path);

#endif /* fileManager_h */
