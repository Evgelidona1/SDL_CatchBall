#ifndef BASKET_H
#define BASKET_H
#include "game.h"

class Basket:public Game
{
public:
    SDL_Event event;
    SDL_Rect dstrect;
    int _x, timerZero, timerNow, timerPause1 = 0, timerPause2 = 0, timerPause = 0, allPause = 0;
    SDL_Surface* score=nullptr;
    SDL_Texture* scoretext=nullptr;
    SDL_Surface* contsurface=nullptr;
    SDL_Texture* cont_texture=nullptr;
    SDL_Texture* basket_texture=nullptr;
    SDL_Surface* basket=nullptr;
    Basket();
    ~Basket();
    void HandleEvent(SDL_Renderer* render);
    void Load(SDL_Renderer* render);
    bool CheckCollision();
};

#endif // BASKET_H
