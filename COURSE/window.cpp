#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "window.h"

using namespace std;

Window::Window()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
        cout<<"Error in SDL_Init"<<SDL_GetError()<<endl;
    if(TTF_Init()==-1)
        cout<<"Error in SDL_TTF"<<TTF_GetError()<<endl;
    window=SDL_CreateWindow("Super Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window==nullptr)
        cout<<"Error SDL_Window"<<SDL_GetError();
    render=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(render==nullptr)
        cout<<"Error SDL_Renderer"<<SDL_GetError();
        //texture
        //screen=SDL_GetWindowSurface(window);
        //if(screen==nullptr)
            //cout<<"Error SDL_Surface"<<SDL_GetError();
    cout<<"WINDOW Constructor by umolchanie"<<endl;
}
Window::~Window()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(screen);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    cout<<"WINDOW Desstructor by umolchanie"<<endl;
}
