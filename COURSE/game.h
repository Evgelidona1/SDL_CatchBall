#ifndef GAME_H
#define GAME_H
#include <SDL.h>
class Game
{
public:
    virtual ~Game()=default;
    virtual void Load(SDL_Renderer* render)=0;
};


#endif // GAME_H
