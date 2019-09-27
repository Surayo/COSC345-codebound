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
#include <termios.h>
#include "fileManager.h"
#include "textManipulation.h"
#include "mylib.h"

/* reads from keypress, doesn't echo */
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void waitKey() {
    char c;
    while ((c = getch()) != EOF && c != '\n') {
        if (c == ' ') {
            return;
        }
    }
}

void freeGame(char *filetext, char *cleantext, FILE *fptr){
    free(filetext);
    free(cleantext);
    closefile(fptr);
    freeAndReset();
}

int main(int argc, const char * argv[]) {
    char *filetext = NULL, *cleantext = NULL;
    char *choiceText = NULL, *choiceFile = NULL;
    char file_location[100], prefix[] = "/Devolution/[", suffix[] = "].txt";
    FILE *fptr = NULL;
    char cwd[300];
    int choiceNum = 0, choice = 0;
    int gameover = 0;
    char *name = NULL;
    char gender = 'm';
    int read = 0;
    size_t len = 0;
    int nameConfirm = 0;
    char choiceGen;
    int i = 0;
    char c;

    //START TITLE
    strcpy(file_location, "/Devolution/[TITLE].txt");
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;
    }
    
    fptr = openfile(cwd, file_location);
    if (fptr == NULL){
        exit(EXIT_FAILURE);
    }
    
    c = fgetc(fptr);
    while(c != EOF) {
        printf("%c", c);
        usleep(500);
        c = fgetc(fptr);
    }
    fclose(fptr);
    sleep(1);
    printf("\n\n\nPRESS ENTER TO CONTINUE\n");
    waitKey();
    system("clear");
    //END TITLE
    
    //START INTRO
    strcpy(file_location, "/Devolution/[INTRO].txt");
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;
    }
    fptr = openfile(cwd, file_location);
    if (fptr == NULL){
        exit(EXIT_FAILURE);
    }
    c = fgetc(fptr);
    while(c != EOF) {
        putchar(c);
        usleep(200);
        c = fgetc(fptr);
    }
    fclose(fptr);
    
    //Character creation
    while (true){
        
        printf("Please enter your name\n");
        while (-1 != read){
            read = getline(&name, &len, stdin);
            if (read > 20){
                printf("Please enter a name less than 20 characters\n");
            } else if (read < 4){
                printf("Please enter a name\n");
            } else {
                break;
            }
        }
        sscanf(name, "%[^\t\n]", name);
        
        printf("Are you male or female? m/f?\n");
        while ((choiceGen = getch()) != EOF) {
            if (choiceGen == 'm') {
                gender = 'm';
                break;
            }
            if (choiceGen == 'f') {
                gender = 'f';
                break;
            }
        }
        printf("\n");
        
        if (gender == 'm'){
            printf("Your name is %s and you're male.\n", name);
        } else{
            printf("Your name is %s and you're female.\n", name);
        }
        printf("Is this correct? y/n?");
        
        while ((choiceNum = getch()) != EOF) {
            int choice = choiceNum - 48;
            
            if (choice == 73) {
                nameConfirm = 1;
                printf("\n");
                break;
            }
            if (choice == 62) {
                nameConfirm = 2;
                printf("\n");
                break;
            }
        }
        if (nameConfirm == 1){
            break;
        }
    }
    
    printf("The story begins");
    fflush(stdout);
    for (i = 0; i < 3; i++){
        printf(" .");
        sleep(1);
        fflush(stdout);
    }
    printf("\n");
    system("clear");
    //END CHAR CREATE //
    //END INTRO
    
    //Load in first text file
    memset(file_location, 0, sizeof(file_location));
    strcpy(file_location, "/Devolution/[C0].txt");
    
    while (true) {
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd() error");
            return 1;
        }
    
        fptr = openfile(cwd, file_location);
        if (fptr == NULL){
            return EXIT_SUCCESS;
        }
        
        filetext = setFile(fptr);
        setBracketPoints(filetext);
    
        //Set the text
        gameover = setStoryText(name, gender);
        cleantext = getCleanText();                                     //this is the STORY text
        //printf("%s\n", cleantext);                                    //story printed here
        int count = 0;
        for(int i = 0; i <strlen(cleantext); i++){
            if (cleantext[i] == '\n' && cleantext[i-1] == '\n') {
                waitKey();
                count = 0;
            }
            if (count > 80 && cleantext[i] == ' ') {
                printf("\n");
                count = 0;
            }
            putchar(cleantext[i]);
            count++;
            fflush(stdout);
        }
        
        if (gameover == 1){
            printf("********************  GAME OVER  ********************\n\n");
            freeGame(filetext, cleantext, fptr);
            break;
            
        } else if (gameover == 2){
            printf("*********************  FINISH  **********************\n\n");
            freeGame(filetext, cleantext, fptr);
            break;
        } else {
            setChoices();
            int choiceAmount = getChoiceAmount();
            //printf("Choices:\n");
            
            printf("*********************  CHOICES  *********************\n\n");
            for (int i = 0; i < choiceAmount; i++){
                printf("%d: ", i + 1);
                choiceText = getChoiceText(i);                      //these are the CHOICES
                count = 0;
                for(int i = 0; i <strlen(choiceText); i++){
                    if (count > 80 && choiceText[i] == ' ') {
                        printf("\n");
                        count = 0;
                    }
                    putchar(choiceText[i]);
                    count++;
                    fflush(stdout);
                }
            }
            printf("\nESC: Exit the game\n");
            
            printf("\n*****************************************************\n\n");
            
            choiceNum = 0;

            fflush(stdin);
            printf("Please enter the corresponding number to make your decision.\n");
            while ((choiceNum = getch()) != EOF) {
                choice = choiceNum - 48;
                //printf("\n%d\n", choice);                                             //printing int corresponding to choice
                //s is 67, b is 50
                if (choice > 0 && choice <= choiceAmount && choice != 0) {
                    choiceFile = getChoiceFile(choice - 1);
                    break;
                } else if (choice == -21) {                                             //escape to exit game, ask to confirm exit
                    printf("Confirm exit game? y/n\n");
                    while ((choiceNum = getch()) != EOF && choiceNum != '\n') {
                        int choice = choiceNum - 48;
                        if (choice == 73) {
                            freeGame(filetext, cleantext, fptr);
                            free(name);
                            exit(EXIT_SUCCESS);
                        }
                        if (choice == 62) {
                            printf("\nGame continued...\n");
                            break;
                        }
                    }
                }
            }
        
            printf("\n");
            choiceText = getChoiceText(choice-1);
            printf("%d: %s", choice, choiceText);
            printf("\n*****************************************************\n\n");
            
            //Setting up next file
            memset(cwd, 0, sizeof(cwd));
            memset(file_location, 0, sizeof(file_location));
            strcpy(file_location, prefix);
            strcat(file_location, choiceFile);
            strcat(file_location, suffix);
        }
        
        //Freeing memory
        freeGame(filetext, cleantext, fptr);
    }
    free(name);
    return EXIT_SUCCESS;
}




