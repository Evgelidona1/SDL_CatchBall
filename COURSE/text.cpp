#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "text.h"
#include <string>

using namespace std;

Text::Text()
{
    font=nullptr;
    menu1=SDL_LoadBMP("menu.bmp");
    if(menu1==nullptr)
    {
        cout<<"Error opening file"<<SDL_GetError();
    }
    cout<<"TEXT Constructor by umolch"<<endl;
}
Text::~Text()
{
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_FreeSurface(menu1);
    cout<<"TEXT Destructor by umolch"<<endl;
}
void Text::OutPrint(SDL_Renderer* render, string vvod, int x, int y, int w, int h)
{

    SDL_Color textcolor={0, 0, 0};
    TTF_Font* font=TTF_OpenFont("EwofiRegular.ttf", 100);
    if(font==nullptr)
        cout<<"Enable to load font"<<TTF_GetError();
    SDL_Surface* textsurface=TTF_RenderText_Solid(font, vvod.c_str(), textcolor);
    SDL_Rect abcposition={x, y, w, h};
    SDL_Texture* mtexture=SDL_CreateTextureFromSurface(render, textsurface);
    SDL_RenderCopy(render, mtexture, nullptr, &abcposition);
    SDL_RenderPresent(render);
    SDL_FreeSurface(textsurface);
}
string Text::InPrint(SDL_Renderer* render, SDL_Texture* texture, string file, string vvod, int x, int y, int w, int h)
{
    bool loop=true;
    int k=0;
    SDL_Event e;
    SDL_FlushEvent(SDL_TEXTINPUT);
    SDL_StartTextInput();
    SDL_Color textcolor={0, 0, 0};
    SDL_Rect abcposition={x, y, w, h};
    SDL_Surface* textsurface=nullptr;
    SDL_Texture* mtexture=nullptr;
    TTF_Font* font=TTF_OpenFont("EwofiRegular.ttf", 60);
    while(loop)
    {
        while(SDL_PollEvent(&e))
        {
            if((e.key.keysym.sym==SDLK_RETURN||vvod.length()>8)&&vvod.size())
            {
                loop=false;
                break;
            }
            else if(e.key.keysym.sym==SDLK_BACKSPACE&&vvod.size())
            {
                //SDL_RenderClear(render);
                vvod.pop_back();
                k--;
            }
            else if(e.type==SDL_TEXTINPUT&&k!=8)
            {
                    vvod+=e.text.text;
                    k++;
            }
        }
        //SDL_RenderClear(render);
        textsurface=TTF_RenderText_Solid(font, vvod.c_str(), textcolor);
        mtexture=SDL_CreateTextureFromSurface(render, textsurface);
        //SDL_RenderClear(render);
        if(vvod.size())
        {
            abcposition.w=textsurface->w;
            abcposition.h=textsurface->h;
            SDL_RenderCopy(render, mtexture, nullptr, &abcposition);
            SDL_DestroyTexture(mtexture);
            SDL_FreeSurface(textsurface);
        }
        SDL_RenderPresent(render);
        SDL_Delay(50);
        //SDL_Render
        //SDL_RenderClear(render);
    }
    SDL_StopTextInput();
    return vvod;
}
void Text::PrintText()
{
    SDL_RenderClear(render);
    texture=SDL_CreateTextureFromSurface(render, menu1);
    SDL_RenderCopy(render, texture, nullptr, nullptr);
    OutPrint(render, "MENU", 237, 60, 140, 90);
    OutPrint(render, "START", 250, 185, 110, 40);
    OutPrint(render, "GAME RULES", 210, 320, 200, 40);
    OutPrint(render, "CHANGE THE PLAYER", 195, 450, 230, 40);
    OutPrint(render, "SEE RECORDS", 210, 575, 190, 40);
    OutPrint(render, "EXIT", 250, 695, 100, 40);
    SDL_DestroyTexture(texture);
}
