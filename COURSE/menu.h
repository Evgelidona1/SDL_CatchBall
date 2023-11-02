#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "text.h"

class Menu: public Text
{
public:
    SDL_Rect RulesRect, RecordsRect, ChangeRect, StartRect, ExitRect, CloseRect, DeleteRecRect, PrintRecRect;
    SDL_Color mycolor={255, 0, 0};
    int b=0, c=0, r=25, i=0;
    string player[10];
    //string name;
    Menu();
    ~Menu();
    void Rules();
    void Load();
    string EnterName();
    void CreateSurfaceFromWidnow(const char* path);
    bool IsMouseInside(int x, int y, SDL_Rect Rect);
    SDL_Surface* records=nullptr;
    SDL_Texture* records_texture=nullptr;
};
#endif // MENU_H_INCLUDED
