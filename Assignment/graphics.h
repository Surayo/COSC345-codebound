//
//  graphics.h
//  Assignment
//
//  Created by Marcus Anderson on 5/16/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#ifndef graphics_h
#define graphics_h

#include "SDL.h"
#include "SDL_ttf.h"

#define STATUS_STATE_TITLE 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2

#define SELECTOR_HOVER_NONE 0
#define SELECTOR_HOVER_C1 1
#define SELECTOR_HOVER_C2 2
#define SELECTOR_HOVER_C3 3
#define SELECTOR_HOVER_NEWGAME 4
#define SELECTOR_HOVER_LOADGAME 5
#define SELECTOR_HOVER_QUITGAME 6
#define SELECTOR_HOVER_BACK 7

#define SELECTOR_SELECT_NONE 0
#define SELECTOR_SELECT_C1 1
#define SELECTOR_SELECT_C2 2
#define SELECTOR_SELECT_C3 3


typedef struct {
    int x, y, w, h;
} Selector;

typedef struct {
    int x, y;
} Choice;

typedef struct {
    //Screen Center coordinates
    int screenCenterX, screenCenterY;
    
    //Selector
    Selector selector;
    int selectorStatus;
    
    //Fonts
    TTF_Font *titleFont;
    TTF_Font *menuFont;
    
    //Textures: contain any text string that we may want to draw
    SDL_Texture *title;
    int titleW, titleH;
    SDL_Texture *newGame;
    int newGameW, newGameH;
    SDL_Texture *loadGame;
    int loadGameW, loadGameH;
    SDL_Texture *quitGame;
    int quitGameW, quitGameH;
    
    //Status
    int statusState;
    
    //Time
    int time;
    
    //Renderer
    SDL_Renderer *renderer;
} GameState;

//prototypes (function references)
extern void createWindow(int boolean);
void doRender(SDL_Renderer *renderer, GameState *game);

#endif /* graphics_h */
