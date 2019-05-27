//
//  gameScreen.c
//  Assignment
//
//  Created by Josef Bode on 5/25/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include "gameScreen.h"
#include "graphics.h"
#include "displayText.h"

const int DISPLAY_W = 1000, DISPLAY_H = 710, CHOICE_W =900, CHOICE_H =40;

void init_game_screen(GameState *game){
    
    game->scenarioStatus = SCENARIO_INTRO;
    
    //move selector to right place and set the right dimensions//
    game->selectorStatus = SELECTOR_HOVER_C1;
    game->selector.x = game->screenCenterX-CHOICE_W/2-2;
    game->selector.y = game->screenCenterY+198;
    game->selector.w = CHOICE_W+4;
    game->selector.h = CHOICE_H+4;
    
    init_display_text(game);
}

void draw_game_screen(GameState *game){
    SDL_Renderer *renderer = game->renderer;
    
    // set the background //
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);                                  //currently set to clear the screen to black
    
    // draw OUTLINE //
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect outlineRect = { game->screenCenterX-DISPLAY_W/2-5, game->screenCenterY-DISPLAY_H/2-5, DISPLAY_W+10, DISPLAY_H+10 };
    SDL_RenderFillRect(renderer, &outlineRect);
    
    // draw the DISPLAY //
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_Rect displayRect = { game->screenCenterX-DISPLAY_W/2, game->screenCenterY-DISPLAY_H/2, DISPLAY_W, DISPLAY_H };
    SDL_RenderFillRect(renderer, &displayRect);
    
    // draw the SELECTOR //
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect selectorRect = { game->selector.x, game->selector.y, game->selector.w, game->selector.h};
    SDL_RenderFillRect(renderer, &selectorRect);
    
    /*
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    if (game->scenarioStatus == SCENARIO_INTRO){
        SDL_Rect continueRect = { game->screenCenterX-CHOICE_W/2, game->screenCenterY+200, CHOICE_W, CHOICE_H };
        SDL_RenderFillRect(renderer, &continueRect);
    } */
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //draw the CHOICE backdrops //
    SDL_Rect choice1BDRect = { game->screenCenterX-CHOICE_W/2, game->screenCenterY+200, CHOICE_W, CHOICE_H };
    SDL_RenderFillRect(renderer, &choice1BDRect);
    SDL_Rect choice2BDRect = { game->screenCenterX-CHOICE_W/2, game->screenCenterY+250, CHOICE_W, CHOICE_H };
    SDL_RenderFillRect(renderer, &choice2BDRect);
    SDL_Rect choice3BDRect = { game->screenCenterX-CHOICE_W/2, game->screenCenterY+300, CHOICE_W, CHOICE_H };
    SDL_RenderFillRect(renderer, &choice3BDRect);
    
    // draw the text //
    draw_display_text(game);
    
    //present what we have drawn
    SDL_RenderPresent(renderer);
}

void shutdown_game_screen(GameState *game){
    shutdown_display_text(game);
}
