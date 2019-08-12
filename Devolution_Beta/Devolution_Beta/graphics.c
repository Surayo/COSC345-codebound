//
//  graphics.c
//  Devolution_Beta
//
//  Created by Josef Bode on 8/5/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include <stdio.h>

#include "graphics.h"
#include "titleScreen.h"
#include "gameScreen.h"
#include "displayText.h"

const int WINDOW_W = 1366, WINDOW_H = 768;

/** When game first launches, load in any required resources and start with the title screen. */
void loadGame(SDL_Renderer *renderer, GameState *game) {
    
    // Load fonts & report an error if a font cannot be located.
    game->titleFont = TTF_OpenFont("Perfect DOS VGA 437.ttf", 156);
    game->subtitleFont = TTF_OpenFont("VCR_OSD_MONO.ttf", 42);
    game->footerFont = TTF_OpenFont("Perfect DOS VGA 437.ttf", 26);
    game->menuFont = TTF_OpenFont("Perfect DOS VGA 437.ttf", 36);
    game->gameFont = TTF_OpenFont("VCR_OSD_MONO.ttf", 16);
    if(!game->titleFont || !game->subtitleFont || !game->menuFont || !game->gameFont || !game->footerFont){
        printf("Cannot find font file!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    // Load images & report an error if an image cannot be located.
    SDL_Surface *selectSurface;
    selectSurface = IMG_Load("selector.png");
    if(selectSurface == NULL) {
        printf("Cannot find selector.png!\n");
        SDL_Quit();
        exit(1);
    }
    game->select = SDL_CreateTextureFromSurface(renderer, selectSurface);
    SDL_FreeSurface(selectSurface);
    
    //set the window center coordinates
    game->screenCenterX = WINDOW_W/2;
    game->screenCenterY = WINDOW_H/2;
    
    //initialise the title screen:
    game->statusState = STATUS_STATE_TITLE;
    init_title_screen(game);
}

/** function for processing any game events */
int processEvents(SDL_Window *window, GameState *game){
    SDL_Event event;
    int done = 0;
    
    //check for events: this while loop will process all the events through PollEvent
    while(SDL_PollEvent(&event) != 0) {
        switch(event.type) {
            case SDL_WINDOWEVENT_CLOSE: {
                if(window) {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
                break;
            case SDL_KEYDOWN: {
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        if (game->statusState == STATUS_STATE_GAME) {
                            game->statusState = STATUS_STATE_TITLE;
                            shutdown_game_screen(game);
                            init_title_screen(game);
                            break;
                        } else {
                            done = 1;
                            break;
                        }
                        break;
                    case SDLK_DOWN:
                        /** menu screen */
                        if (game->selectorStatus == SELECTOR_HOVER_NEWGAME) {
                            game->selector.y = game->screenCenterY+75;
                            game->selectorStatus = SELECTOR_HOVER_LOADGAME;
                            break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_LOADGAME) {
                            game->selector.y = game->screenCenterY+155;
                            game->selectorStatus = SELECTOR_HOVER_QUITGAME;
                            break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_QUITGAME) {
                            game->selector.y = game->screenCenterY-15;
                            game->selectorStatus = SELECTOR_HOVER_NEWGAME;
                            break;
                        }
                        // MOVE CHOICE SELECTOR
                        if (game->scenarioStatus == SCENARIO_LASTPAGE) {
                            if (game->selectorStatus == SELECTOR_HOVER_C1) {
                                game->selector.y = game->screenCenterY+250;
                                game->selectorStatus = SELECTOR_HOVER_C2;
                                break;
                            }
                            if (game->selectorStatus == SELECTOR_HOVER_C2) {
                                game->selector.y = game->screenCenterY+300;
                                game->selectorStatus = SELECTOR_HOVER_C3;
                                break;
                            }
                            if (game->selectorStatus == SELECTOR_HOVER_C3) {
                                game->selector.y = game->screenCenterY+200;
                                game->selectorStatus = SELECTOR_HOVER_C1;
                                break;
                            }
                        }
                        break;
                    case SDLK_UP: {
                        if (game->selectorStatus == SELECTOR_HOVER_NEWGAME) {
                            game->selector.y = game->screenCenterY+155;
                            game->selectorStatus = SELECTOR_HOVER_QUITGAME;
                            break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_LOADGAME) {
                            game->selector.y = game->screenCenterY-15;
                            game->selectorStatus = SELECTOR_HOVER_NEWGAME;
                            break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_QUITGAME) {
                            game->selector.y = game->screenCenterY+75;
                            game->selectorStatus = SELECTOR_HOVER_LOADGAME;
                            break;
                        }
                        // MOVE CHOICE SELECTOR
                        if (game->scenarioStatus == SCENARIO_LASTPAGE) {
                            if (game->selectorStatus == SELECTOR_HOVER_C1) {
                                game->selector.y = game->screenCenterY+300;
                                game->selectorStatus = SELECTOR_HOVER_C3;
                                break;
                            }
                            if (game->selectorStatus == SELECTOR_HOVER_C2) {
                                game->selector.y = game->screenCenterY+200;
                                game->selectorStatus = SELECTOR_HOVER_C1;
                                break;
                            }
                            if (game->selectorStatus == SELECTOR_HOVER_C3) {
                                game->selector.y = game->screenCenterY+250;
                                game->selectorStatus = SELECTOR_HOVER_C2;
                                break;
                            }
                        }
                        break;
                    }
                    case SDLK_LEFT: {
                        if (game->scenarioStatus == SCENARIO_STORY) {
                            prevPage(game);
                            break;
                        }
                        break;
                    }
                    case SDLK_RIGHT: {
                        if (game->scenarioStatus == SCENARIO_STORY) {
                            nextPage(game);
                            break;
                        }
                        break;
                    }
                    case SDLK_SPACE:
                        /** select NEWGAME */
                        if (game->selectorStatus == SELECTOR_HOVER_NEWGAME) {
                            game->statusState = STATUS_STATE_GAME;
                            game->scenarioStatus = SCENARIO_INTRO;
                            shutdown_title_screen(game);
                            init_game_screen(game);
                            break;
                        }
                        /** continue from intro */
                        if (game->scenarioStatus == SCENARIO_INTRO) {
                            nextPage(game);
                            game->pageStatus = PAGE1;
                        }
                        /** SELECT FIRST CHOICE */
                        if (game->selectorStatus == SELECTOR_HOVER_C1) {
                            
                            break;
                        }
                        /** quit game is pressed */
                        if (game->selectorStatus == SELECTOR_HOVER_QUITGAME) {
                            done = 1;
                            break;
                        }
                }
            }
                break;
            case SDL_QUIT:
                done = 1;
                break;
        }
    }
    return done;
}

/** render the display */
void doRender(SDL_Renderer *renderer, GameState *game){
    if(game->statusState == STATUS_STATE_TITLE) {
        draw_title_screen(game);
    } else if (game->statusState == STATUS_STATE_GAME) {
        draw_game_screen(game);
    } else if (game->statusState == STATUS_STATE_GAMEOVER){
        //draw_end_screen(game); (game over screen)
    }
}

/** Initialise SDL2 and create an application window for the game. */
void createWindow(int boolean){
    if (boolean == 1) {
        
        GameState gameState;
        SDL_Window *window;                     //Declare a window
        SDL_Renderer *renderer;                 //Declare a renderer
        
        SDL_Init(SDL_INIT_VIDEO);               //Initialise SDL2 library
        
        //create an application window with the following settings:
        window = SDL_CreateWindow("COSC 345 Project: Devolution",                   //window title
                                  SDL_WINDOWPOS_UNDEFINED,                          //initial x pos
                                  SDL_WINDOWPOS_UNDEFINED,                          //initial y pos
                                  WINDOW_W,                                         //width, in pixels
                                  WINDOW_H,                                         //height, in pixels
                                  SDL_WINDOW_OPENGL);                               //flags
        
        //create the renderer we will be using throughout the program:
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        gameState.renderer = renderer;          //Pass renderer to gameState
        
        TTF_Init();                             //initialise font library
        
        loadGame(renderer, &gameState);         //load the game with necessary resources & begin with title screen
        
        /** Event loop: constantly checks for events */
        int done = 0;
        while(!done) {
            done = (processEvents(window, &gameState));     //check for events
            doRender(renderer, &gameState);                 //render the display
        }
        
        /** Shutdown the game and unload all memory */
        if(gameState.title != NULL)
            SDL_DestroyTexture(gameState.title);
        if(gameState.subtitle != NULL)
            SDL_DestroyTexture(gameState.subtitle);
        if(gameState.footer != NULL)
            SDL_DestroyTexture(gameState.footer);
        if(gameState.newGame != NULL)
            SDL_DestroyTexture(gameState.newGame);
        if(gameState.loadGame != NULL)
            SDL_DestroyTexture(gameState.loadGame);
        if(gameState.quitGame != NULL)
            SDL_DestroyTexture(gameState.quitGame);
        if(gameState.mainText != NULL)
            SDL_DestroyTexture(gameState.mainText);
        if(gameState.choice1Text != NULL)
            SDL_DestroyTexture(gameState.choice1Text);
        if(gameState.choice2Text != NULL)
            SDL_DestroyTexture(gameState.choice2Text);
        if(gameState.choice3Text != NULL)
            SDL_DestroyTexture(gameState.choice3Text);
        
        TTF_CloseFont(gameState.titleFont);
        TTF_CloseFont(gameState.subtitleFont);
        TTF_CloseFont(gameState.footerFont);
        TTF_CloseFont(gameState.menuFont);
        TTF_CloseFont(gameState.gameFont);
        SDL_DestroyTexture(gameState.select);
        
        //close and destroy the window:
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        
        //clean up:
        TTF_Quit();
        SDL_Quit();
    }
}
