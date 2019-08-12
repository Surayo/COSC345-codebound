//
//  gameScreen.c
//  Devolution_Beta
//
//  Created by Josef Bode on 8/5/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include "gameScreen.h"
#include "graphics.h"
#include "displayText.h"

void init_game_screen(GameState *game){
    //Initialise selector
    game->selectorStatus = SELECTOR_HOVER_C1;
    game->selector.x = game->screenCenterX-400;
    game->selector.y = game->screenCenterY+300;
    
    init_display_text(game);
}

void draw_game_screen(GameState *game){
    const int DISPLAY_W = 1000, DISPLAY_H = 710;
    SDL_Renderer *renderer = game->renderer;
    
    // set the background //
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // draw OUTLINE //
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect outlineRect = { game->screenCenterX-DISPLAY_W/2-5, game->screenCenterY-DISPLAY_H/2-5, DISPLAY_W+10, DISPLAY_H+10 };
    SDL_RenderFillRect(renderer, &outlineRect);
    // draw the DISPLAY //
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_Rect displayRect = { game->screenCenterX-DISPLAY_W/2, game->screenCenterY-DISPLAY_H/2, DISPLAY_W, DISPLAY_H };
    SDL_RenderFillRect(renderer, &displayRect);
    
    // draw the SELECTOR if at last page
    if (game->scenarioStatus == SCENARIO_LASTPAGE) {
        SDL_Rect selectRect = { game->selector.x, game->selector.y, 20, 20 };
        SDL_RenderCopy(renderer, game->select, NULL, &selectRect);
    }
    
    // draw the TEXT
    draw_display_text(game);
    
    SDL_RenderPresent(renderer);
}

void shutdown_game_screen(GameState *game){
    shutdown_display_text(game);
}
