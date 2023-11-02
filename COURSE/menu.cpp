#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "menu.h"
using namespace std;

Menu::Menu()
{
    cout<<"MENU Constructor by umolch"<<endl;
    records=SDL_LoadBMP("records.bmp");
    records_texture=SDL_CreateTextureFromSurface(render, records);
    RulesRect.x=RecordsRect.x=StartRect.x=ChangeRect.x=ExitRect.x=149;
    RulesRect.y=298;ChangeRect.y=434;RecordsRect.y=558;StartRect.y=162;ExitRect.y=685;
    RulesRect.w=RecordsRect.w=StartRect.w=ChangeRect.w=ExitRect.w=315;
    RulesRect.h=RecordsRect.h=StartRect.h=ChangeRect.h=ExitRect.h=100;
    CloseRect.x=547;CloseRect.y=0;CloseRect.w=53;CloseRect.h=50;
    DeleteRecRect={0, 760, 100, 40};PrintRecRect={500, 760, 100, 40};
}
Menu::~Menu()
{
    SDL_FreeSurface(records);
    SDL_DestroyTexture(records_texture);
    cout<<"MENU Destructor by umolch"<<endl;
}
bool Menu::IsMouseInside(int x, int y, SDL_Rect Rect)
{
    bool inside=true;
    if(x<Rect.x)inside=false;
    else if(x>Rect.x+Rect.w)inside=false;
    else if(y<Rect.y)inside=false;
    else if(y>Rect.y+Rect.h)inside=false;
    return inside;
}
string Menu::EnterName()
{
    string name;
    SDL_Surface *nameof=SDL_LoadBMP("heroname.bmp");
    if (nameof==nullptr)
    {
        cout<<"meow"<<endl;
        cout<<"error of load surface"<<SDL_GetError()<<endl;
    }
    SDL_Texture *texture=SDL_CreateTextureFromSurface(render, nameof);
    SDL_RenderCopy(render, texture, nullptr, nullptr);
    OutPrint(render, "ENTER YOUR NAME", 200, 360, 190, 40);
    name=InPrint(render, texture, "heroname.bmp", name, 180, 420, 20, 20);
    if(name==" ")
        name="Unknown";
    return name;
}
void Menu::Rules()
{
    SDL_Surface* gamerules=nullptr;
    gamerules=SDL_LoadBMP("gamerules.bmp");
    if (gamerules==nullptr)
        cout<<"error of load surface"<<SDL_GetError()<<endl;
    SDL_Texture* rules_texture=SDL_CreateTextureFromSurface(render, gamerules);
    if(rules_texture==nullptr)
        cout<<"error of creating textures"<<SDL_GetError()<<endl;
    SDL_RenderCopy(render, rules_texture, nullptr, nullptr);
    SDL_RenderPresent(render);
    SDL_DestroyTexture(rules_texture);
    SDL_FreeSurface(gamerules);
}
void Menu::Load()
{
    records=SDL_LoadBMP("records.bmp");
    if (records==nullptr)
        cout<<"error of load surface"<<SDL_GetError()<<endl;
    records_texture=SDL_CreateTextureFromSurface(render, records);
    if(records_texture==nullptr)
        cout<<"error of creating textures"<<SDL_GetError()<<endl;
}
void Menu::CreateSurfaceFromWidnow(const char* path)
{
    screen=SDL_GetWindowSurface(window);
    records=SDL_LoadBMP(path);
    SDL_BlitSurface(records, nullptr, screen, nullptr);
    SDL_UpdateWindowSurface(window);
}
