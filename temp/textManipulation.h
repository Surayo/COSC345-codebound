//  textManipulation.h
//  Assignment
//
//  Created by Marcus Anderson on 5/9/19.
//  Copyright © 2019 CodeBound. All rights reserved.

#ifndef textManipulation_h
#define textManipulation_h

typedef struct choice *choices;

extern char* setFile(FILE *fptr);
extern void setBracketPoints(char *filetext);
extern char* getCurrentFile(void);
extern void setStoryText(char *filetext);
extern char* getCleanText(void);
extern void freeText(void);
extern void setChoices(char *filetext);

#endif /* textManipulation_h */
