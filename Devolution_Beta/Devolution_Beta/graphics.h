//
//  graphics.h
//  Devolution_Beta
//
//  Created by Josef Bode on 8/5/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#ifndef graphics_h
#define graphics_h

#include "SDL.h"
#include "SDL_ttf.h"

#define STATUS_STATE_TITLE 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2

#define SELECTOR_HOVER_CONTINUE 0
#define SELECTOR_HOVER_C1 1
#define SELECTOR_HOVER_C2 2
#define SELECTOR_HOVER_C3 3
#define SELECTOR_HOVER_NEWGAME 4
#define SELECTOR_HOVER_LOADGAME 5
#define SELECTOR_HOVER_QUITGAME 6

#define SCENARIO_INTRO 0
#define SCENARIO_STORY 1
#define SCENARIO_LASTPAGE 2

#define PAGE1 1
#define PAGE2 2
#define PAGE3 3

#define SELECT_NON 0
#define SELECT_C1 1
#define SELECT_C2 2
#define SELECT_C3 3

typedef struct {
    int x, y;
} Selector;

typedef struct {
    int x, y;
} Choice;

typedef struct {
    int screenCenterX, screenCenterY;
    
    //Selector
    Selector selector;
    
    //Images
    SDL_Texture *select;
    
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
    SDL_Texture *instructions;
    int instructionsW, instructionsH;
    
    SDL_Texture *newGame;
    int newGameW, newGameH;
    SDL_Texture *loadGame;
    int loadGameW, loadGameH;
    SDL_Texture *quitGame;
    int quitGameW, quitGameH;
    
    SDL_Texture *mainText;
    int mainTextW, mainTextH;
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
    int pageStatus;
    int selectedChoice;

    //Renderer
    SDL_Renderer *renderer;
} GameState;

//prototypes (function references)
void loadGame(SDL_Renderer *renderer, GameState *game);
int processEvents(SDL_Window *window, GameState *game);
void doRender(SDL_Renderer *renderer, GameState *game);
extern void createWindow(int boolean);

#endif /* graphics_h */
