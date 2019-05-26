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
    
    //Intro text:
    char *story = NULL;
    story = "Welcome to DEVOLUTION\n\nAs a text-based adventure, the player chooses how the story unfolds.\n\n\n\nPress continue to begin the story...";
    
    //Continue text:
    char *choice1 = NULL;
    choice1 = "Continue";
    
    /*
    char *cwd = NULL;
    char file_location[50];
    char *text = NULL;
    //char *choice = NULL, *next_file = NULL;
    FILE *fptr;
    cwd = emalloc(150 * sizeof(char));
    cwd = current_directory(cwd);
    strcpy(file_location, "/Devolution/C0.txt");
    fptr = openfile(cwd, file_location);
    text = setFile(fptr);
    store_brackets(text);
    text = getCleanText();
     */
    
    //create any text to be used on the game screen//
    //Story text:
    SDL_Color white = { 255, 255, 255, 255};                                                    //text colour set to white
    SDL_Surface *tmp0 = TTF_RenderText_Blended_Wrapped(game->gameFont, story, white, 900);       //use a surface to hold the text
    game->storyTextW = tmp0->w;                                                                 //store the width of the text
    game->storyTextH = tmp0->h;                                                                 //store the height of the text
    game->storyText = SDL_CreateTextureFromSurface(game->renderer, tmp0);                       //create texture from text surface
    SDL_FreeSurface(tmp0);                                                                      //destroy surface
    //CHOICES text:
    SDL_Surface *tmp1 = TTF_RenderText_Blended_Wrapped(game->gameFont, choice1, white, 900);
    game->choice1TextW = tmp1->w;
    game->choice1TextH = tmp1->h;
    game->choice1Text = SDL_CreateTextureFromSurface(game->renderer, tmp1);
    SDL_FreeSurface(tmp0);
    
    //fclose(fptr);
    //free(cwd);
}

void draw_display_text(GameState *game){
    SDL_Renderer *renderer = game->renderer;
    
    // draw the STORY TEXT //
    SDL_Rect storyRect = { game->screenCenterX-game->storyTextW/2, game->screenCenterY-320, game->storyTextW, game->storyTextH};
    SDL_RenderCopy(renderer, game->storyText, NULL, &storyRect);
}

void shutdown_display_text(GameState *game){
    
}
