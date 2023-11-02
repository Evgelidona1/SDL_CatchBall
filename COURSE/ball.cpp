#include "ball.h"
#include <iostream>
using namespace std;
Ball::Ball()
{
    cout<<"Ball Constructor by umolch"<<endl;
}
Ball::~Ball()
{
    SDL_DestroyTexture(ball_texture);
    SDL_FreeSurface(ball);
    cout<<"Ball Destructor by umolch"<<endl;
}
void Ball::Load(SDL_Renderer* render)
{
    ball=SDL_LoadBMP("ball.bmp");
    if(ball==nullptr)
        cout<<"Unable to load surface"<<SDL_GetError<<endl;
    else
    {
        SDL_SetColorKey(ball, SDL_TRUE, SDL_MapRGB(ball->format, 210, 198, 208));
        ball_texture=SDL_CreateTextureFromSurface(render, ball);
        if(ball_texture==nullptr)
            cout<<"Unable to create texture"<<SDL_GetError<<endl;
        else
        {
            SDL_RenderCopy(render, ball_texture, nullptr, &recty);
        }
    }
}
