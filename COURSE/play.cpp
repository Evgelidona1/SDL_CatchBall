#include "play.h"
#include <ctime>
#include <sstream>
using namespace std;
Play::Play()
{
    x1=recty.x;
    y1=recty.y;
    x2=recty1.x;
    y2=recty1.y;
    x3=recty2.x;
    y3=recty2.y;
    x4=recty3.x;
    y4=recty3.y;
    AddExit.x=547;AddExit.y=0;AddExit.w=53;AddExit.h=50;
    cout<<"PLAY constructor by umolch"<<endl;
}
Play::~Play()
{
    SDL_DestroyTexture(game_texture);
    TTF_CloseFont(font);
    TTF_Quit();
    cout<<"PLAY destructor by umolch"<<endl;
}
bool Play::Pause()
{
    SDL_FlushEvent(SDLK_p);
    bool quit=false;
    bool a=false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(IsMouseInside(x, y, AddExit))
                {
                    a=true;
                    quit=true;
                    break;
                }
            }
            else if(e.key.keysym.sym==SDLK_SPACE)
            {
                a=false;
                quit=true;
                break;
            }
        }
    }
    return a;
}
bool Play::IsMouseInside(int x, int y, SDL_Rect Rect)
{
    bool inside=true;
    if(x<Rect.x)inside=false;
    else if(x>Rect.x+Rect.w)inside=false;
    else if(y<Rect.y)inside=false;
    else if(y>Rect.y+Rect.h)inside=false;
    return inside;
}
string Play::Score(SDL_Renderer* render, int x, int y, int w, int h, int score)
{
    stringstream ss;
    string str;
    ss<<score;
    str=ss.str();
    if(TTF_Init()<0)
        cout<<"TTF error"<<SDL_GetError()<<endl;
    font=TTF_OpenFont("EwofiRegular.ttf", 40);
    if(font==nullptr)
        cout<<"unable to load font"<<TTF_GetError()<<endl;
    SDL_Color color={0, 0, 0};
    SDL_Rect location={x, y, w, h};
    SDL_Surface* textsurface=nullptr;
    textsurface=TTF_RenderText_Solid(font, str.c_str(), color);
    x=textsurface->w;y=textsurface->h;
    location.w=x;location.h=y;
    if(textsurface==nullptr)
        cout<<"Unable to load surface"<<SDL_GetError()<<endl;
    SDL_Texture* texture=SDL_CreateTextureFromSurface(render, textsurface);
    if(texture==nullptr)
        cout<<"Unable create texture from surface"<<SDL_GetError()<<endl;
    SDL_FreeSurface(textsurface);
    SDL_RenderCopy(render, texture, nullptr, &location);
    return str;
}
string Play::play(SDL_Renderer* render)
{
    string s;
    SDL_Surface* game=SDL_LoadBMP("gamewall.bmp");
    if(game==nullptr)
        cout<<"error of load surface"<<SDL_GetError()<<endl;
    game_texture=SDL_CreateTextureFromSurface(render, game);
    Ball::Load(render);
    Basket::Load(render);
    stringstream timetext;
    int counter=0;bool flag=true, k=false;
    timerZero=time(NULL);
    //timerPause=time(NULL);
    bool quit=false;
    while(!quit)
    {
        SDL_Event event;
        timerPause1 = timerPause2 = 0;
        timerNow=time(NULL);
        if(SDL_PollEvent(&event))
        {
            if(event.type==SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_LEFT:
                     _x-=20;
                     break;
                case SDLK_RIGHT:
                    _x+=20;
                     break;
                }
            }
            if(event.key.keysym.sym==SDLK_p)
            {
                timerPause = 0;
                timerPause1=time(NULL)-timerZero;
                //cout<<timerPause<<endl;
                SDL_Surface* PauseSurf=SDL_LoadBMP("pause.bmp");
                if(PauseSurf==nullptr)
                {
                    cout<<"SDL_Load BMP error"<<SDL_GetError()<<endl;
                }
                SDL_Texture* PauseTexture=SDL_CreateTextureFromSurface(render, PauseSurf);
                SDL_FreeSurface(PauseSurf);
                if(PauseTexture==nullptr)
                {
                    cout<<"SDL_CreateTextureFromSurface error"<<SDL_GetError()<<endl;
                }
                SDL_RenderCopy(render, PauseTexture, nullptr, nullptr);
                SDL_RenderPresent(render);
                quit=Pause();
                SDL_RenderClear(render);
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(event.type==SDL_MOUSEBUTTONDOWN&&IsMouseInside(x, y, AddExit))
                {
                    SDL_RenderCopy(render, scoretext, nullptr, nullptr);
                    s=Score(render, 270, 300, 120, 120, counter);
                    SDL_RenderPresent(render);
                    quit=true;
                    break;
                }
                timerPause2=time(NULL)-timerZero;
                timerPause = timerPause2 - timerPause1;
                allPause += timerPause;
            }
        }
        if(timerNow-timerZero-allPause<10)
        {
            y1+=8;
            if(y1==800)
            {
                y1=0;
                x1=0+rand()%555;
                flag=true;
            }
            if((y1>=730&&y1<=800&&x1>=_x-5&&x1<=_x+88)&&flag)
            {
                counter++;
                flag=false;
            }
        }
        if(timerNow-timerZero-allPause>=10&&timerNow-timerZero-allPause<=20)
        {
            y2+=8;
            if(y2==800)
            {
                y2=0;
                x2=350+rand()%370;
                flag=true;
            }
            if((y2>=730&&y2<=800&&x2>=_x-5&&x2<=_x+88)&&flag)
            {
                counter++;
                flag=false;
            }
            y1+=8;
            if(y1==800)
            {
                y1=0;
                x1=0+rand()%300;
                flag=true;
            }
            if((y1>=730&&y1<=800&&x1>=_x-5&&x1<=_x+88)&&flag)
            {
                counter++;
                flag=false;
            }
        }
        if(timerNow-timerZero-allPause>20&&timerNow-timerZero-allPause<=50)
        {
            y3+=8;
            if(y3==800)
            {
                y3=0;
                x3=350+rand()%370;
                flag=true;
            }
            if((y3>=730&&y3<=800&&x3>=_x-5&&x3<=_x+88)&&flag)
            {
                counter++;
                flag=false;
            }
            y2+=8;
            if(y2==800)
            {
                y2=0;
                x2=150+rand()%200;
                flag=true;
            }
            if((y2>=730&&y2<=800&&x2>=_x-45&&x2<=_x+128)&&flag)
            {
                counter++;
                flag=false;
            }
            y1+=8;
            if(y1==800)
            {
                y1=0;
                x1=0+rand()%50;
                flag=true;
            }
            if((y1>=730&&y1<=800&&x1>=_x-5&&x1<=_x+88)&&flag)
            {
                counter++;
                flag=false;
            }
        }
        if(timerNow-timerZero-allPause>50&&timerNow-timerZero-allPause<60)
        {
            y4+=8;
            if(y4==800)
            {
                y4=0;
                x4=0+rand()%500;
                flag=true;
            }
            if((y4>=730&&y4<=800&&x4>=_x-5&&x4<=_x+88)&&flag)
            {
                counter++;
                flag=false;
            }
            y3+=8;
            if(y3==800)
            {
                y3=0;
                x3=300+rand()%350;
                flag=true;
            }
            if((y3>=730&&y3<=800&&x3>=_x-5&&x3<=_x+88)&&flag)
            {
                counter++;
                flag=false;
            }
            y2+=8;
            if(y2==800)
            {
                y2=0;
                x2=100+rand()%150;
                flag=true;
            }
            if((y2>=730&&y2<=800&&x2>=_x-45&&x2<=_x+128)&&flag)
            {
                counter++;
                flag=false;
            }
            y1+=8;
            if(y1==800)
            {
                y1=0;
                x1=0+rand()%50;
                flag=true;
            }
            if((y1>=730&&y1<=800&&x1>=_x-5&&x1<=_x+88)&&flag)
            {
                counter++;
                flag=false;
            }
        }
        if(timerNow-timerZero-allPause<10)
        {
            recty={x1, y1, 45, 45};
        }
        if(timerNow-timerZero-allPause>=10&&timerNow-timerZero-allPause<=20)
        {
            recty={x1, y1, 45, 45};
            recty1={x2, y2, 45, 45};
        }
        if(timerNow-timerZero-allPause>20&&timerNow-timerZero-allPause<=50)
        {
            recty={x1, y1, 45, 45};
            recty1={x2, y2, 45, 45};
            recty2={x3, y3, 45, 45};
        }
        if(timerNow-timerZero-allPause>50&&timerNow-timerZero-allPause<60)
        {
            recty={x1, y1, 45, 45};
            recty1={x2, y2, 45, 45};
            recty2={x3, y3, 45, 45};
            recty3={x4, y4, 45, 45};
        }
        //recty={x1, y1, 45, 45};
        dstrect={_x, 720, 128, 85};
        SDL_RenderClear(render);
        SDL_RenderCopy(render, game_texture, nullptr, nullptr);
        if(timerNow-timerZero-allPause<10)
            SDL_RenderCopy(render, ball_texture, nullptr, &recty);
        //SDL_RenderCopy(render, ball_texture, nullptr, &recty);
        if(timerNow-timerZero-allPause>=10&&timerNow-timerZero-allPause<=20)
        {
            SDL_RenderCopy(render, ball_texture, nullptr, &recty);
            SDL_RenderCopy(render, ball_texture, nullptr, &recty1);
        }
        if(timerNow-timerZero-allPause>20&&timerNow-timerZero-allPause<=50)
        {
            SDL_RenderCopy(render, ball_texture, nullptr, &recty);
            SDL_RenderCopy(render, ball_texture, nullptr, &recty1);
            SDL_RenderCopy(render, ball_texture, nullptr, &recty2);
        }
        if(timerNow-timerZero-allPause>50&&timerNow-timerZero-allPause<60)
        {
            SDL_RenderCopy(render, ball_texture, nullptr, &recty);
            SDL_RenderCopy(render, ball_texture, nullptr, &recty1);
            SDL_RenderCopy(render, ball_texture, nullptr, &recty2);
            SDL_RenderCopy(render, ball_texture, nullptr, &recty3);
        }
        SDL_RenderCopy(render, basket_texture, nullptr, &dstrect);
        Score(render, 130, 3, 55, 55, counter);
        Score(render, 100, 43, 55, 55, (timerNow-timerZero-allPause));
        if(timerNow-timerZero-allPause == 10)
        {
            SDL_RenderCopy(render, scoretext, nullptr, nullptr);
            s=Score(render, 270, 300, 120, 120, counter);
            SDL_RenderPresent(render);
            quit=true;
            SDL_Delay(2000);
            break;
        }
        SDL_RenderPresent(render);
    }
    if (s != "");
        return s;
    return s;
}
void Play::Close(SDL_Renderer* render)
{
    TTF_CloseFont(font);
    font=nullptr;
}
