//
//  displayText.c
//  Assignment
//
//  Created by Josef Bode on 5/26/19.
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
#include "fileLoader.h"
#include "mylib.h"

void init_display_text(GameState *game){
    
    // Intro text: //
    //char *story = NULL;
    //story = "Welcome to DEVOLUTION\n\nAs a text-based adventure, the player chooses how the story unfolds.\n\n\n\nPress continue to begin the story...";
    
    // Continue text: //
    //char *choice1 = NULL;
    //choice1 = "Continue";
    
    char *cwd = NULL;
    char file_location[50];
    char *story = NULL;
    char *choice1 = NULL;
    char *choice2 = NULL;
    char *choice3 = NULL;
    //char *next_file = NULL;
    FILE *fptr;
    
    cwd = emalloc(150 * sizeof(char));
    cwd = current_directory(cwd);
    
    if (game->scenarioStatus == SCENARIO_C0){
        strcpy(file_location, "/Devolution/C0.txt");
        fptr = openfile(cwd, file_location);
        story = setFile(fptr);
        store_brackets(story);
        story = getCleanText();
        choice1 = getChoiceText(1);
        choice2 = getChoiceText(2);
        choice3 = getChoiceText(3);
        freeChoices();
        fclose(fptr);
        free(cwd);
    }
    
    if (game->scenarioStatus == SCENARIO_C0_1) {
        strcpy(file_location, "/Devolution/C0.1.txt");
        fptr = openfile(cwd, file_location);
        story = setFile(fptr);
        store_brackets(story);
        story = getCleanText();
        choice1 = getChoiceText(1);
        choice2 = getChoiceText(2);
        choice3 = getChoiceText(3);
        freeChoices();
        fclose(fptr);
        free(cwd);
    }
    
    if (game->scenarioStatus == SCENARIO_C0_2) {
        cwd = emalloc(150 * sizeof(char));
        cwd = current_directory(cwd);
        strcpy(file_location, "/Devolution/C0.2.txt");
        fptr = openfile(cwd, file_location);
        story = setFile(fptr);
        store_brackets(story);
        story = getCleanText();
        choice1 = getChoiceText(1);
        choice2 = getChoiceText(2);
        choice3 = getChoiceText(3);
        freeChoices();
        fclose(fptr);
        free(cwd);
    }
    
    
    //create any text to be used on the game screen//
    //Story text:
    SDL_Color white = { 255, 255, 255, 255};                                                    //text colour set to white
    SDL_Surface *tmp0 = TTF_RenderText_Blended_Wrapped(game->gameFont, story, white, 900);      //use a surface to hold the text
    game->storyTextW = tmp0->w;                                                                 //store the width of the text
    game->storyTextH = tmp0->h;                                                                 //store the height of the text
    game->storyText = SDL_CreateTextureFromSurface(game->renderer, tmp0);                       //create texture from text surface
    SDL_FreeSurface(tmp0);                                                                      //destroy surface
    //CHOICES text:
    //choice 1:
    SDL_Surface *tmp1 = TTF_RenderText_Blended_Wrapped(game->gameFont, choice1, white, 800);
    game->choice1TextW = tmp1->w;
    game->choice1TextH = tmp1->h;
    game->choice1Text = SDL_CreateTextureFromSurface(game->renderer, tmp1);
    SDL_FreeSurface(tmp1);
    if (game->scenarioStatus == SCENARIO_C0_2){
        //choice 2:
        SDL_Surface *tmp2 = TTF_RenderText_Blended_Wrapped(game->gameFont, choice2, white, 800);
        game->choice2TextW = tmp2->w;
        game->choice2TextH = tmp2->h;
        game->choice2Text = SDL_CreateTextureFromSurface(game->renderer, tmp2);
        SDL_FreeSurface(tmp2);
        //choice 3:
        SDL_Surface *tmp3 = TTF_RenderText_Blended_Wrapped(game->gameFont, choice3, white, 800);
        game->choice3TextW = tmp3->w;
        game->choice3TextH = tmp3->h;
        game->choice3Text = SDL_CreateTextureFromSurface(game->renderer, tmp3);
        SDL_FreeSurface(tmp3);
    }
}

void draw_display_text(GameState *game){
    SDL_Renderer *renderer = game->renderer;
    
    // draw the STORY text //
    SDL_Rect storyRect = { game->screenCenterX-game->storyTextW/2, game->screenCenterY-320, game->storyTextW, game->storyTextH};
    SDL_RenderCopy(renderer, game->storyText, NULL, &storyRect);
    
    // draw the CHOICES text //
    SDL_Rect choice1Rect = { game->screenCenterX-game->choice1TextW/2, game->screenCenterY+205, game->choice1TextW, game->choice1TextH};
    SDL_RenderCopy(renderer, game->choice1Text, NULL, &choice1Rect);
    SDL_Rect choice2Rect = { game->screenCenterX-game->choice2TextW/2, game->screenCenterY+255, game->choice2TextW, game->choice2TextH};
    SDL_RenderCopy(renderer, game->choice2Text, NULL, &choice2Rect);
    SDL_Rect choice3Rect = { game->screenCenterX-game->choice3TextW/2, game->screenCenterY+305, game->choice3TextW, game->choice3TextH};
    SDL_RenderCopy(renderer, game->choice3Text, NULL, &choice3Rect);
}

void changeScenario(GameState *game){
    if (game->scenarioStatus == SCENARIO_C0) {
        game->scenarioStatus = SCENARIO_C0_1;
        init_display_text(game);
        return;
    }
    
    if (game->scenarioStatus == SCENARIO_C0_1) {
        game->scenarioStatus = SCENARIO_C0_2;
        init_display_text(game);
        return;
    }
}


void shutdown_display_text(GameState *game){
    SDL_DestroyTexture(game->storyText);
    SDL_DestroyTexture(game->choice1Text);
    SDL_DestroyTexture(game->choice2Text);
    SDL_DestroyTexture(game->choice3Text);
    
    game->storyText = NULL;
}
