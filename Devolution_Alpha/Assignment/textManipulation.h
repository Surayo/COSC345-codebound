//
//  textManipulation.h
//  Assignment
//
//  Created by Marcus Anderson on 5/9/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#ifndef textManipulation_h
#define textManipulation_h

typedef struct choice *choices;

extern char* setFile(FILE *fptr);
extern void store_brackets(char *filetext);
extern char* getCleanText();
extern char* getNextFile(int num);
extern char* getChoiceText(int num);
extern void freeChoices();

#endif /* textManipulation_h */
