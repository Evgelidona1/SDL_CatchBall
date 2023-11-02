#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

class Window
{
public:
    int SCREEN_WIDTH=600;
    int SCREEN_HEIGHT=800;
    SDL_Window *window=nullptr;
    SDL_Renderer* render=nullptr;
    SDL_Surface* screen=nullptr;
    SDL_Texture* texture=nullptr;
    SDL_Event* event=nullptr;
    Window(){}
    ~Window(){}
};


#endif // WINDOW_H_INCLUDED
