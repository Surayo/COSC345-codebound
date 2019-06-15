//
//  graphics.c
//  Assignment
//
//  Created by Marcus Anderson on 5/16/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include "SDL.h"
#include "SDL_ttf.h"

#include "graphics.h"
#include "titleScreen.h"
#include "gameScreen.h"
#include "displayText.h"

#include <stdio.h>
#include <time.h>

const int WINDOW_W = 1366, WINDOW_H = 768;

/** When game first launches, load in any required resources and start with the title screen. */
void loadGame(GameState *game) {
    
    // Load fonts & report an error if a font cannot be located
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
    while(SDL_PollEvent(&event)) {
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
                switch(event.key.keysym.sym) {                              //keyboard events go here
                    case SDLK_ESCAPE:                                       //check to see if escape key has been pressed
                        if (game->statusState == STATUS_STATE_GAME) {       //if the SELECTOR is hovered over NEWGAME
                            game->statusState = STATUS_STATE_TITLE;         //begin a new game - load the game screen
                            shutdown_game_screen(game);
                            init_title_screen(game);
                            break;
                        } else {
                            done = 1;
                        break;
                        }
                break;
                    case SDLK_DOWN:
                        if (game->selectorStatus == SELECTOR_HOVER_NEWGAME) {
                            game->selector.x = game->screenCenterX-game->loadGameW/2-25;
                            game->selector.y = game->screenCenterY+85;
                            game->selector.w = game->loadGameW+50;
                            game->selector.h = game->loadGameH+30;
                            game->selectorStatus = SELECTOR_HOVER_LOADGAME;
                        break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_LOADGAME) {
                            game->selector.x = game->screenCenterX-game->quitGameW/2-25;
                            game->selector.y = game->screenCenterY+185;
                            game->selector.w = game->quitGameW+50;
                            game->selector.h = game->quitGameH+30;
                            game->selectorStatus = SELECTOR_HOVER_QUITGAME;
                        break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_QUITGAME) {
                            game->selector.x = game->screenCenterX-game->newGameW/2-25;
                            game->selector.y = game->screenCenterY-15;
                            game->selector.w = game->newGameW+50;
                            game->selector.h = game->newGameH+30;
                            game->selectorStatus = SELECTOR_HOVER_NEWGAME;
                        break;
                        }
                        if (game->scenarioStatus == SCENARIO_C0_2) {
                            if (game->selectorStatus == SELECTOR_HOVER_C1) {
                                game->selector.y = game->screenCenterY+248;
                                game->selectorStatus = SELECTOR_HOVER_C2;
                            break;
                            }
                            if (game->selectorStatus == SELECTOR_HOVER_C2) {
                                game->selector.y = game->screenCenterY+298;
                                game->selectorStatus = SELECTOR_HOVER_C3;
                            break;
                            }
                            if (game->selectorStatus == SELECTOR_HOVER_C3) {
                                game->selector.y = game->screenCenterY+198;
                                game->selectorStatus = SELECTOR_HOVER_C1;
                            break;
                            }
                        }
                        break;
                    case SDLK_UP: {
                        if (game->selectorStatus == SELECTOR_HOVER_NEWGAME) {
                            game->selector.x = game->screenCenterX-game->quitGameW/2-25;
                            game->selector.y = game->screenCenterY+185;
                            game->selector.w = game->quitGameW+50;
                            game->selector.h = game->quitGameH+30;
                            game->selectorStatus = SELECTOR_HOVER_QUITGAME;
                        break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_LOADGAME) {
                            game->selector.x = game->screenCenterX-game->newGameW/2-25;
                            game->selector.y = game->screenCenterY-15;
                            game->selector.w = game->newGameW+50;
                            game->selector.h = game->newGameH+30;
                            game->selectorStatus = SELECTOR_HOVER_NEWGAME;
                        break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_QUITGAME) {
                            game->selector.x = game->screenCenterX-game->loadGameW/2-25;
                            game->selector.y = game->screenCenterY+85;
                            game->selector.w = game->loadGameW+50;
                            game->selector.h = game->loadGameH+30;
                            game->selectorStatus = SELECTOR_HOVER_LOADGAME;
                        break;
                        }
                        if (game->scenarioStatus == SCENARIO_C0_2) {
                            if (game->selectorStatus == SELECTOR_HOVER_C1) {
                                game->selector.y = game->screenCenterY+298;
                                game->selectorStatus = SELECTOR_HOVER_C3;
                            break;
                            }
                            if (game->selectorStatus == SELECTOR_HOVER_C2) {
                                game->selector.y = game->screenCenterY+198;
                                game->selectorStatus = SELECTOR_HOVER_C1;
                            break;
                            }
                            if (game->selectorStatus == SELECTOR_HOVER_C3) {
                                game->selector.y = game->screenCenterY+248;
                                game->selectorStatus = SELECTOR_HOVER_C2;
                            break;
                            }
                        }
                        break;
                    }
                    case SDLK_RETURN:                                               //return key is pressed
                        if (game->selectorStatus == SELECTOR_HOVER_NEWGAME) {       //if the SELECTOR is hovered over NEWGAME
                            game->statusState = STATUS_STATE_GAME;                  //begin a new game - load the game screen
                            game->scenarioStatus = SCENARIO_C0;
                            shutdown_title_screen(game);
                            init_game_screen(game);
                        break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_C1) {
                            changeScenario(game);
                        break;
                        }
                        if (game->selectorStatus == SELECTOR_HOVER_QUITGAME) { 
                            done = 1;
                        break;
                        }
                }
            }
                break;
            case SDL_QUIT:
                //quit out of the game
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
        if (game->selector.y == 540-game->newGameH) {
            game->selectorStatus = SELECTOR_HOVER_NEWGAME;
        }
    } else if (game->statusState == STATUS_STATE_GAME) {
        draw_game_screen(game);
    } else if (game->statusState == STATUS_STATE_GAMEOVER){
        //gameOverScreen(game);
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

        loadGame(&gameState);                   //load the game with necessary resources & begin with title screen
        
        //at this point the window is open: enter program loop (using SDL_PollEvent)
        int done = 0;
        //Event loop: constantly checks for events (tied to fps, but I used a delay in case VSYNC doesn't work)
        while(!done) {
            //check for events:
            done = (processEvents(window, &gameState));
            
            //render the display:
            doRender(renderer, &gameState);
            
            //wait 100 milliseconds for every frame (so we don't burn out CPU)
            //SDL_Delay(100);
        }
        
        // Shutdown the game and unload all memory //
        if(gameState.storyText != NULL)
            SDL_DestroyTexture(gameState.storyText);
        TTF_CloseFont(gameState.titleFont);
        TTF_CloseFont(gameState.subtitleFont);
        TTF_CloseFont(gameState.footerFont);
        TTF_CloseFont(gameState.menuFont);
        TTF_CloseFont(gameState.gameFont);
        
        //close and destroy the window:
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);

        //clean up:
        TTF_Quit();
        SDL_Quit();
    }
}
