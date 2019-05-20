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

void create_window(){
    const int WIDTH = 1000, HEIGHT = 800;
    
    //GameState = ganeState;
    SDL_Window *window;                     //Declare a window
    SDL_Renderer *renderer;                 //Declare a renderer
    
    SDL_Init(SDL_INIT_VIDEO);               //Initialise SDL2
    
    //create an application window with the following settings:
    window = SDL_CreateWindow("Game Window",                //window title
                              SDL_WINDOWPOS_UNDEFINED,      //initial x pos
                              SDL_WINDOWPOS_UNDEFINED,      //initial y pos
                              WIDTH,                        //width, in pixels
                              HEIGHT,                       //height, in pixels
                              SDL_WINDOW_FULLSCREEN);       //flags
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    //the window is open: enter program loop (SDL_PollEvent)
    int done = 0;
    SDL_Event event;
    
    //Event loop:
    while(!done) {
        //check for events:
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if(window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                    }
                }
                break;
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            done = 1;
                        break;
                    }
                }
                break;
                case SDL_QUIT:
                    //quit out of the game
                    done = 1;
                break;
            }
        }
        
        //render display settings:
        //set the drawing colour to gray
        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
        
        //clear the screen to gray
        SDL_RenderClear(renderer);
        
        //present what we have drawn
        SDL_RenderPresent(renderer);
        
        //slight delay (don't burn out CPU)
        SDL_Delay(100);
    }
    
    //close and destroy the window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    //clean up
    SDL_Quit();
}
