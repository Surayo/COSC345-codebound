//
//  titleScreen.c
//  Devolution_Beta
//
//  Created by Josef Bode on 8/5/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include "titleScreen.h"
#include "graphics.h"

void init_title_screen(GameState *game){
    SDL_Color white = { 255, 255, 255, 255};
    SDL_Color faded = { 255, 255, 255, 90};
    
    //Title text:
    SDL_Surface *tmp0 = TTF_RenderText_Blended(game->titleFont, "Devolution", white);       //use a surface to hold the text
    game->titleW = tmp0->w;                                                                 //store the width of the text
    game->titleH = tmp0->h;                                                                 //store the height of the text
    game->title = SDL_CreateTextureFromSurface(game->renderer, tmp0);                       //create texture from text surface
    SDL_FreeSurface(tmp0);                                                                  //destroy surface
    //Subtitle text:
    SDL_Surface *tmp1 = TTF_RenderText_Blended(game->subtitleFont, "A text based adventure . . .", white);
    game->subtitleW = tmp1->w;
    game->subtitleH = tmp1->h;
    game->subtitle = SDL_CreateTextureFromSurface(game->renderer, tmp1);
    SDL_FreeSurface(tmp1);
    //Footer text:
    SDL_Surface *tmp2 = TTF_RenderText_Blended(game->footerFont, "CodeBound 2019", white);
    game->footerW = tmp2->w;
    game->footerH = tmp2->h;
    game->footer = SDL_CreateTextureFromSurface(game->renderer, tmp2);
    SDL_FreeSurface(tmp2);
    //Instructions text:
    SDL_Surface *tmp3 = TTF_RenderText_Blended_Wrapped(game->footerFont, "Use the arrow keys to move selector Press spacebar to select an option", white, 600);
    game->instructionsW = tmp3->w;
    game->instructionsH = tmp3->h;
    game->instructions = SDL_CreateTextureFromSurface(game->renderer, tmp3);
    SDL_FreeSurface(tmp3);
    //NEWGAME text
    SDL_Surface *tmp4 = TTF_RenderText_Blended(game->menuFont, "New Game", white);
    game->newGameW = tmp4->w;
    game->newGameH = tmp4->h;
    game->newGame = SDL_CreateTextureFromSurface(game->renderer, tmp4);
    SDL_FreeSurface(tmp4);
    //LOADGAME text
    SDL_Surface *tmp5 = TTF_RenderText_Blended(game->menuFont, "Continue", faded);
    game->loadGameW = tmp5->w;
    game->loadGameH = tmp5->h;
    game->loadGame = SDL_CreateTextureFromSurface(game->renderer, tmp5);
    SDL_FreeSurface(tmp5);
    //QUITGAME text
    SDL_Surface *tmp6 = TTF_RenderText_Blended(game->menuFont, "Quit Game", white);
    game->quitGameW = tmp6->w;
    game->quitGameH = tmp6->h;
    game->quitGame = SDL_CreateTextureFromSurface(game->renderer, tmp6);
    SDL_FreeSurface(tmp6);
    //Initialise the selector
    game->selectorStatus = SELECTOR_HOVER_NEWGAME;
    game->selector.x = game->screenCenterX-100;
    game->selector.y = game->screenCenterY-15;
}

void draw_title_screen(GameState *game){
    const int DISPLAY_W = 1000, DISPLAY_H = 710;
    SDL_Renderer *renderer = game->renderer;
    
    // set the BACKGROUND //
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
    
    // draw the SELECTOR
    SDL_Rect selectRect = { game->selector.x, game->selector.y, 20, 20 };
    SDL_RenderCopy(renderer, game->select, NULL, &selectRect);
    
    // draw the GAME TITLE //
    SDL_Rect titleRect = { game->screenCenterX-game->titleW/2, game->screenCenterY-330, game->titleW, game->titleH};
    SDL_RenderCopy(renderer, game->title, NULL, &titleRect);
    // draw the SUBTITLE //
    SDL_Rect subtitleRect = { game->screenCenterX-game->subtitleW/2, game->screenCenterY-150, game->subtitleW, game->subtitleH};
    SDL_RenderCopy(renderer, game->subtitle, NULL, &subtitleRect);
    // draw the FOOTER //
    SDL_Rect footerRect = { game->screenCenterX+270, game->screenCenterY+315, game->footerW, game->footerH};
    SDL_RenderCopy(renderer, game->footer, NULL, &footerRect);
    // draw the INSTRUCTIONS //
    SDL_Rect instrRect = { game->screenCenterX-480, game->screenCenterY+290, game->instructionsW, game->instructionsH};
    SDL_RenderCopy(renderer, game->instructions, NULL, &instrRect);
    
    // draw the NEWGAME option //
    SDL_Rect newGameRect = { game->screenCenterX-50, game->screenCenterY-20, game->newGameW, game->newGameH};
    SDL_RenderCopy(renderer, game->newGame, NULL, &newGameRect);
    // draw the LOADGAME option //
    SDL_Rect loadGameRect = { game->screenCenterX-50, game->screenCenterY+70, game->loadGameW, game->loadGameH};
    SDL_RenderCopy(renderer, game->loadGame, NULL, &loadGameRect);
    // draw the QUITGAME option //
    SDL_Rect quitGameRect = { game->screenCenterX-50, game->screenCenterY+150, game->quitGameW, game->quitGameH};
    SDL_RenderCopy(renderer, game->quitGame, NULL, &quitGameRect);
    
    SDL_RenderPresent(renderer);
}

void shutdown_title_screen(GameState *game){
    SDL_DestroyTexture(game->title);
    SDL_DestroyTexture(game->subtitle);
    SDL_DestroyTexture(game->newGame);
    SDL_DestroyTexture(game->loadGame);
    SDL_DestroyTexture(game->quitGame);
    SDL_DestroyTexture(game->footer);
    game->title = NULL;
    game->subtitle = NULL;
    game->newGame = NULL;
    game->loadGame = NULL;
    game->quitGame = NULL;
    game->footer = NULL;
}
