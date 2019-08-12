//
//  displayText.c
//  Devolution_Beta
//
//  Created by Josef Bode on 8/5/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "displayText.h"
#include "graphics.h"

#include "textManipulation.h"
#include "fileManager.h"
#include "mylib.h"

char *filetext = NULL, *cleantext = NULL;
char *choiceText = NULL, *choiceFile = NULL;
char file_location[100], prefix[] = "/Devolution/[", suffix[] = "].txt";
FILE *fptr = NULL;
char cwd[300];

void init_display_text(GameState *game){
    SDL_Color white = { 255, 255, 255, 255 };
    char *story = NULL, *choice1 = NULL, *choice2 = NULL, *choice3 = NULL;
    
    if (game->scenarioStatus == SCENARIO_INTRO) {
        strcpy(file_location, "/Devolution/[C0].txt");
    }
    
    if (game->scenarioStatus == SCENARIO_STORY) {
        printf("\n\n\nI GOT HERE\n\n\n");
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current working dir: %s\n", cwd);
        } else {
            perror("getcwd() error");
            exit(1);
        }
        
        fptr = openfile(cwd, file_location);
        if (fptr == NULL){
            exit(1);
        }
        filetext = setFile(fptr);
        setBracketPoints(filetext);
        
        //Set the text
        setStoryText();
        story = getCleanText();
        printf("%s\n", cleantext);
        setChoices();
        
        choiceText = getChoiceText(0);
        choiceFile = getChoiceFile(0);
        
        //Setting up next file
        memset(cwd, 0, sizeof(cwd));
        memset(file_location, 0, sizeof(file_location));
        strcpy(file_location, prefix);
        strcat(file_location, choiceFile);
        strcat(file_location, suffix);
    }
    
    
    if (game->scenarioStatus == SCENARIO_INTRO) {
        story = "PUT INTRODUCTION HERE!\n\nSPACEBAR TO CONTINUE";
    }
    
    // create any text to be used as the main body of the game screen //
    SDL_Surface *tmp0 = TTF_RenderText_Blended_Wrapped(game->gameFont, story, white, 900);
    game->mainTextW = tmp0->w;
    game->mainTextH = tmp0->h;
    game->mainText = SDL_CreateTextureFromSurface(game->renderer, tmp0);
    SDL_FreeSurface(tmp0);
    
    if (game->scenarioStatus == SCENARIO_LASTPAGE) {
        //CHOICES text:
        SDL_Surface *tmp1 = TTF_RenderText_Blended_Wrapped(game->gameFont, choice1, white, 800);
        game->choice1TextW = tmp1->w;
        game->choice1TextH = tmp1->h;
        game->choice1Text = SDL_CreateTextureFromSurface(game->renderer, tmp1);
        SDL_FreeSurface(tmp1);
        SDL_Surface *tmp2 = TTF_RenderText_Blended_Wrapped(game->gameFont, choice2, white, 800);
        game->choice2TextW = tmp2->w;
        game->choice2TextH = tmp2->h;
        game->choice2Text = SDL_CreateTextureFromSurface(game->renderer, tmp2);
        SDL_FreeSurface(tmp2);
        SDL_Surface *tmp3 = TTF_RenderText_Blended_Wrapped(game->gameFont, choice3, white, 800);
        game->choice3TextW = tmp3->w;
        game->choice3TextH = tmp3->h;
        game->choice3Text = SDL_CreateTextureFromSurface(game->renderer, tmp3);
        SDL_FreeSurface(tmp3);
    }
    //Freeing memory
    free(filetext);
    free(cleantext);
    closefile(fptr);
    freeAndReset();
}

void draw_display_text(GameState *game){
    SDL_Renderer *renderer = game->renderer;
    
    // draw the MAIN body of text //
    SDL_Rect mainRect = { game->screenCenterX-game->mainTextW/2, game->screenCenterY-320, game->mainTextW, game->mainTextH};
    SDL_RenderCopy(renderer, game->mainText, NULL, &mainRect);
    
    if (game->scenarioStatus == SCENARIO_LASTPAGE) {
        // draw the CHOICES //
        SDL_Rect choice1Rect = { game->screenCenterX-game->choice1TextW/2, game->screenCenterY+210, game->choice1TextW, game->choice1TextH};
        SDL_RenderCopy(renderer, game->choice1Text, NULL, &choice1Rect);
        SDL_Rect choice2Rect = { game->screenCenterX-game->choice2TextW/2, game->screenCenterY+260, game->choice2TextW, game->choice2TextH};
        SDL_RenderCopy(renderer, game->choice2Text, NULL, &choice2Rect);
        SDL_Rect choice3Rect = { game->screenCenterX-game->choice3TextW/2, game->screenCenterY+310, game->choice3TextW, game->choice3TextH};
        SDL_RenderCopy(renderer, game->choice3Text, NULL, &choice3Rect);
    }
    
}

void nextPage(GameState *game){
    if (game->scenarioStatus == SCENARIO_INTRO) {
        game->scenarioStatus = SCENARIO_STORY;
        init_display_text(game);
        return;
    }
    if (game->pageStatus == PAGE1) {
        game->pageStatus = PAGE2;
        init_display_text(game);
        return;
    }
    if (game->pageStatus == PAGE2) {
        game->pageStatus = PAGE3;
        init_display_text(game);
        return;
    }
}

void prevPage(GameState *game) {
    if (game->pageStatus == PAGE3) {
        game->pageStatus = PAGE2;
        init_display_text(game);
        return;
    }
    if (game->pageStatus == PAGE2) {
        game->pageStatus = PAGE1;
        init_display_text(game);
        return;
    }
}

void shutdown_display_text(GameState *game){
    SDL_DestroyTexture(game->mainText);
    SDL_DestroyTexture(game->choice1Text);
    SDL_DestroyTexture(game->choice2Text);
    SDL_DestroyTexture(game->choice3Text);
    game->mainText = NULL;
    game->choice1Text = NULL;
    game->choice2Text = NULL;
    game->choice3Text = NULL;
}
