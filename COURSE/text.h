#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include <string.h>
#include "window.h"

using namespace std;
class Text: public Window
{
public:
    string s;
    TTF_Font* font=nullptr;
    SDL_Surface *menu1=nullptr;
    Text();
     ~Text();
    void OutPrint(SDL_Renderer* render, string vvod, int x, int y, int w, int h);
    string InPrint(SDL_Renderer* render, SDL_Texture* texture, string file, string vvod, int x, int y, int w, int h);
    void PrintText();
};

#endif
