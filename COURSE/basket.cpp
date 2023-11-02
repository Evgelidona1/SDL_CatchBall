#include "basket.h"
#include <iostream>
using namespace std;
Basket::Basket()
{
    dstrect.x=236;dstrect.y=730;dstrect.w=128;dstrect.h=85;
    _x=dstrect.x;
    cout<<"Basket Constructor by umolch"<<endl;
}
Basket::~Basket()
{
    SDL_DestroyTexture(cont_texture);
    SDL_DestroyTexture(scoretext);
    SDL_DestroyTexture(basket_texture);
    SDL_FreeSurface(basket);
    SDL_FreeSurface(score);
    SDL_FreeSurface(contsurface);
    cout<<"Basket Destructor by umolch"<<endl;
}
void Basket::Load(SDL_Renderer* render)
{
    basket=SDL_LoadBMP("basket.bmp");
    if(basket==nullptr)
        cout<<"Unable to load surface"<<SDL_GetError<<endl;
    else
    {
        SDL_SetColorKey(basket, SDL_TRUE, SDL_MapRGB(basket->format, 210, 198, 208));
        basket_texture=SDL_CreateTextureFromSurface(render, basket);
        if(basket_texture==nullptr)
            cout<<"Unable to create texture"<<SDL_GetError<<endl;
        else
            SDL_RenderCopy(render, basket_texture, nullptr, &dstrect);
    }
    contsurface=SDL_LoadBMP("pause.bmp");
    if(contsurface==nullptr)
        cout<<"Error of load surface"<<SDL_GetError()<<endl;
    else
    {
        cont_texture=SDL_CreateTextureFromSurface(render, contsurface);
        if(cont_texture==nullptr)
            cout<<"Unable to create texture"<<SDL_GetError()<<endl;
    }
    score=SDL_LoadBMP("finalscore.bmp");
    if(score==nullptr)
        cout<<"ERROR OF LOAD SURFACE"<<SDL_GetError()<<endl;
    scoretext=SDL_CreateTextureFromSurface(render, score);
    if(scoretext==nullptr)
        cout<<"Unable to create texture"<<SDL_GetError()<<endl;
}
