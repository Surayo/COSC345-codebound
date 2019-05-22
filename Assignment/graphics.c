//
//  graphics.c
//  Assignment
//
//  Created by Marcus Anderson on 5/16/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#include "graphics.h"
#include "SDL.h"
//#include "SDL_ttf.h"
#include <stdio.h>

typedef struct {
    int x, y;
} Selector;

int processEvents(SDL_Window *window, Selector *selector){
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
                switch(event.key.keysym.sym) { //keyboard events go here
                    case SDLK_ESCAPE: //check to see if escape key has been pressed
                        done = 1;
                    break;
                    case SDLK_UP:
                        if (selector->y == 595) {
                            selector->y = 715;
                            break;
                        }
                        if (selector->y == 655) {
                            selector->y = 595;
                            break;
                        }
                        if (selector->y == 715) {
                            selector->y = 655;
                            break;
                        }
                    case SDLK_DOWN:
                        if (selector->y == 595) {
                            selector->y = 655;
                            break;
                        }
                        if (selector->y == 655) {
                            selector->y = 715;
                            break;
                        }
                        if (selector->y == 715) {
                            selector->y = 595;
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

void doRender(SDL_Renderer *renderer, Selector *selector){
    //set the drawing colour to gray
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    
    //clear the screen to gray (background colour)
    SDL_RenderClear(renderer);
    
    //set the drawing colour to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Rect selectorPanel = { selector->x, selector->y, 790, 60 };
    SDL_RenderFillRect(renderer, &selectorPanel);
    
    //set the drawing colour to darker gray
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    
    //draw the main text panel { x, y, width, height }
    SDL_Rect mainPanel = { 100, 40, 800, 500 };
    SDL_RenderFillRect(renderer, &mainPanel);
    
    //draw the main text panel { x, y, width, height }
    SDL_Rect choice1Panel = { 110, 600, 780, 50 };
    SDL_RenderFillRect(renderer, &choice1Panel);
    
    //draw the main text panel { x, y, width, height }
    SDL_Rect choice2Panel = { 110, 660, 780, 50 };
    SDL_RenderFillRect(renderer, &choice2Panel);
    
    //draw the main text panel { x, y, width, height }
    SDL_Rect choice3Panel = { 110, 720, 780, 50 };
    SDL_RenderFillRect(renderer, &choice3Panel);
    
    //present what we have drawn
    SDL_RenderPresent(renderer);
}

void createWindow(){
    const int WIDTH = 1000, HEIGHT = 800;
    
    //GameState = ganeState;
    SDL_Window *window;                     //Declare a window
    SDL_Renderer *renderer;                 //Declare a renderer
    
    SDL_Init(SDL_INIT_VIDEO);               //Initialise SDL2
    
    Selector selector;
    selector.x = 105;
    selector.y = 595;
    
    //create an application window with the following settings:
    window = SDL_CreateWindow("Game Window",                //window title
                              SDL_WINDOWPOS_UNDEFINED,      //initial x pos
                              SDL_WINDOWPOS_UNDEFINED,      //initial y pos
                              WIDTH,                        //width, in pixels
                              HEIGHT,                       //height, in pixels
                              SDL_WINDOW_OPENGL);           //flags
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    
    //the window is open: enter program loop (SDL_PollEvent)
    int done = 0;
    
    //Event loop: constantly checks for events - tied to fps
    while(!done) {
        
        //check for events:
        done = (processEvents(window, &selector));
        
        //render display:
        doRender(renderer, &selector);
        
        //wait 100 milliseconds for every frame (don't burn out CPU)
        SDL_Delay(100);
    }
    
    //close and destroy the window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    //clean up
    SDL_Quit();
}
