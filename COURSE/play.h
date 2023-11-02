#ifndef PLAY_H
#define PLAY_H
#include <iostream>
#include <string.h>
#include "SDL_ttf.h"
#include "ball.h"
#include "basket.h"
using namespace std;
class Play:public Ball, public Basket
{
public:
    SDL_Rect recty={0, 0, 45, 45};
    SDL_Rect recty1={300, 0, 45, 45};
    SDL_Rect recty2={400, 0, 45, 45};
    SDL_Rect recty3={450, 0, 45, 45};
    SDL_Rect AddExit;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    SDL_Texture* game_texture=nullptr;
    TTF_Font* font=nullptr;
    Play();
    ~Play();
    string play(SDL_Renderer* render);
    bool IsMouseInside(int x, int y, SDL_Rect Rect);
    string Score(SDL_Renderer* render, int x, int y, int w, int h, int score);
    string ReturnScore();
    bool Pause();
    void Close(SDL_Renderer* render);
};


#endif // PLAY_H
