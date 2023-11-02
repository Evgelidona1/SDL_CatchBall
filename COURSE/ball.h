#ifndef BALL_H
#define BALL_H
#include "game.h"
class Ball:public Game
{
public:
    SDL_Texture* ball_texture=nullptr;
    SDL_Surface* ball=nullptr;
    SDL_Rect recty={0, 0, 45, 45};
    Ball();
    ~Ball();
    void Load(SDL_Renderer* render);
};


#endif // BALL_H
