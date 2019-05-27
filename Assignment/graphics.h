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

#define SCENARIO_INTRO 0
#define SCENARIO_C0 1

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
    
    //Fonts
    TTF_Font *titleFont;
    TTF_Font *subtitleFont;
    TTF_Font *footerFont;
    TTF_Font *menuFont;
    TTF_Font *gameFont;
    
    //Textures: contain any text string that we may want to draw
    SDL_Texture *title;
    int titleW, titleH;
    SDL_Texture *subtitle;
    int subtitleW, subtitleH;
    SDL_Texture *footer;
    int footerW, footerH;
    SDL_Texture *newGame;
    int newGameW, newGameH;
    SDL_Texture *loadGame;
    int loadGameW, loadGameH;
    SDL_Texture *quitGame;
    int quitGameW, quitGameH;
    SDL_Texture *storyText;
    int storyTextW, storyTextH;
    SDL_Texture *choice1Text;
    int choice1TextW, choice1TextH;
    SDL_Texture *choice2Text;
    int choice2TextW, choice2TextH;
    SDL_Texture *choice3Text;
    int choice3TextW, choice3TextH;
    
    //Status
    int statusState;
    int scenarioStatus;
    int selectorStatus;
    
    //Time
    int time;
    
    //Renderer
    SDL_Renderer *renderer;
} GameState;

//prototypes (function references)
extern void createWindow(int boolean);
void doRender(SDL_Renderer *renderer, GameState *game);

#endif /* graphics_h */
