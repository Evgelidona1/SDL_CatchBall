#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

class Window
{
public:
    int SCREEN_WIDTH=600;
    int SCREEN_HEIGHT=800;
    SDL_Window *window=nullptr;
    SDL_Renderer* render=nullptr;
    SDL_Surface* screen=nullptr;
    SDL_Texture* texture=nullptr;
    SDL_Event* event=nullptr;
    Window();
    ~Window();
};
Window::Window()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
        cout<<"Error in SDL_Init"<<SDL_GetError()<<endl;
    if(TTF_Init()==-1)
        cout<<"Error in SDL_TTF"<<TTF_GetError()<<endl;
    window=SDL_CreateWindow("Super Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window==nullptr)
        cout<<"Error SDL_Window"<<SDL_GetError();
    render=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(render==nullptr)
        cout<<"Error SDL_Renderer"<<SDL_GetError();
    cout<<"WINDOW Constructor by umolchanie"<<endl;
}
Window::~Window()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(screen);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    cout<<"WINDOW Desstructor by umolchanie"<<endl;
}
class Text: public Window
{
public:
    string s;
    TTF_Font* font=nullptr;
    SDL_Surface *menu1=nullptr;
    Text();
     ~Text();
    void OutPrint(SDL_Renderer* render, string vvod, int x, int y, int w, int h);
    string InPrint(SDL_Renderer* render, SDL_Texture* texture, string file, string vvod, int x, int y, int w, int h);
    void PrintText();
};
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
    string kostl;
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
                cout<<vvod<<endl;
                k--;
                SDL_RenderClear(render);
                SDL_Surface *nameof=SDL_LoadBMP("heroname.bmp");
                if (nameof==nullptr)
                    cout<<"error of load surface"<<SDL_GetError()<<endl;
                SDL_Texture *texture=SDL_CreateTextureFromSurface(render, nameof);
                SDL_RenderCopy(render, texture, nullptr, nullptr);
                OutPrint(render, "ENTER YOUR NAME", 200, 360, 190, 40);

                textsurface=TTF_RenderText_Solid(font, vvod.c_str(), textcolor);
                mtexture=SDL_CreateTextureFromSurface(render, textsurface);

                //OutPrint(render, vvod, x, y, w, h);
                SDL_RenderPresent(render);
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
class File
{
public:
    File();
    ~File();
    void BinFile(string *name);
    void PrintText(SDL_Surface* te, SDL_Window* window, int x, int y, int w, int h, string vvod);
    void Convert();
    void Clear();
    void Start(SDL_Surface* screen, SDL_Window* window);
};
File::File()
{
    cout<<"FILE Constructor by umolch"<<endl;
}
File::~File()
{
    cout<<"FILE Destructor by umolch"<<endl;
}
void File::BinFile(string* name)
{
    ofstream a;
    size_t len;
    string t;
    string tmp_res[10];
    string tup1, tup2;
    bool flag=false;
    int j = 0;
    //tup1+=tmp
    for (int i = 0; i < 11; i++)
    {
        if (name[i] != "")
        {
            if( i < 10 ) tmp_res[i] = name[i];
            else //if( i == 10 )
            {
                cout<<"name[10] = " << name[i] << endl;
                tup1 = tmp_res[9][tmp_res[9].length()-2];
                tup1+=tmp_res[9][tmp_res[9].length()-1];
                tup2 = name[10][name[10].length()-2];
                tup2+=name[10][name[10].length()-1];
                cout << "tup1 = " << tup1 << "tup2 = " << tup2 << endl;
                if(tup2>=tup1 && !flag )
                {
                    flag=true;
                    cout << " tup2 >= tup1 " << endl;
                    cout << " tmp_res[9] = " << tmp_res[9] << endl;
                    tmp_res[9] = name[10];
                    name[10] = "";
                    cout << " tmp_res[9] = " << tmp_res[9] << endl;
                    //break;
                }
                if (flag = true)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        name[i] = tmp_res[i];
                        cout << "name[i] = " << name[i] << endl;
                    }
                    flag=false;
                }
            }

            for(int i=1;i<10;i++)
            {
                for(int j=9;j>=i;j--)
                {
                    if (tmp_res[j-1] != "" && tmp_res[j] != "")
                    {
                        tup1 = tmp_res[j-1][tmp_res[j-1].length()-2];
                        tup1+=tmp_res[j-1][tmp_res[j-1].length()-1];
                        tup2 = tmp_res[j][tmp_res[j].length()-2];
                        tup2+=tmp_res[j][tmp_res[j].length()-1];
                        //cout << "tup1 = " << tup1 << " tup2 = " << tup2 << endl;
                        if(tup1<tup2)
                        {
                            t=tmp_res[j-1];
                            tmp_res[j-1]=tmp_res[j];
                            tmp_res[j]=t;
                            //cout << "tmp_res[j-1] = " << tmp_res[j-1] << " tmp_res[j] = " << tmp_res[j] << endl;
                            tup1.clear(); tup2.clear();
                        }
                    }

                }
            }

        }
    }
    a.open("file.bin", ios::out | ios::binary);
    for(int i=0;i<10;i++)
    {
        if(tmp_res[i]!="")
        {
            cout << "tmp_res[i] = " << tmp_res[i] << endl;
            tmp_res[i]+='\r';
            len=tmp_res[i].length();
            a.write(tmp_res[i].c_str(), len);
        }
    }
    a.close();
}
void File::PrintText(SDL_Surface* te, SDL_Window* window, int x, int y, int w, int h, string vvod)
{
    if(SDL_Init(SDL_INIT_VIDEO)<0)
        cout<<"SDL Error"<<SDL_GetError()<<endl;
    if(TTF_Init()<0)
        cout<<"TTF Open Error"<<TTF_GetError()<<endl;
    TTF_Font* font=TTF_OpenFont("EwofiRegular.ttf", 60);
    if(font==nullptr)
        cout<<"Enable to load font"<<TTF_GetError();
    SDL_Color textcolor={0, 0, 0};
    SDL_Surface* textsurface=TTF_RenderText_Solid(font, vvod.c_str(), textcolor);
    SDL_Rect abcposition={x, y, w, h};
    if(textsurface==nullptr)
    {
        cout<<"error of load textsurface"<<SDL_GetError()<<endl;
        cout<<"meow"<<endl;
    }
        //cout<<"error of load textsurface"<<SDL_GetError()<<endl;
    SDL_BlitSurface(textsurface, nullptr, te, &abcposition);
    SDL_UpdateWindowSurface(window);

}
void File::Convert()
{
    ifstream::pos_type size;
    char* buff;
    ifstream in("file.bin", ios::binary|ios::in|ios::ate);
    if(!in.is_open())return;
    size=in.tellg();
    buff=new char[size];
    in.seekg(0, ios::beg);
    in.read(buff, size);
    in.close();
    ofstream out;
    out.open("rec.txt", ios::out|ios::trunc);
    if(!out.is_open())return;
    out.write(buff, size);
    out.close();
    delete[]buff;
}
void File::Clear()
{
    remove("file.bin");
    ifstream in("file.bin", ios::binary);
    if(!in.is_open())return;
    else in.close();
}
void File::Start(SDL_Surface* screen, SDL_Window* window)
{
    char b=0;
    string h[11];
    int i=0;
    ifstream in("file.bin", ios::binary|ios::in);
    while(!in.eof())
    {
        b=in.get();
            h[i]+=b;
            while( b != '\r'&&!(in.eof()))
            {
                b=in.get();
                h[i]+=b;

            }
            h[i].pop_back();
            i++;
    }
    in.close();
    int y=150;
    for(int i=0;i<10;i++)
    {
        if(h[i]!="")
        {
            cout << "h[i] = " << h[i] << endl;
            PrintText(screen, window, 100, y, 80, 20, h[i]);
            y+=50;
        }
    }
    SDL_UpdateWindowSurface(window);
}
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

class Game
{
public:
    virtual ~Game()=default;
    virtual void Load(SDL_Renderer* render)=0;
};


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
    void Load(SDL_Renderer* render);
};
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
    bool Pause();
    void Close(SDL_Renderer* render);
};
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
        if(timerNow-timerZero-allPause == 60)
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



int main(int argc, char** argv)
{
    Menu menu;
    Play CatchTheBall;
    File file;
    string name, result;
    string player[11];int i=0, in_count=0;
    string tmp[11];
    string samename;
    SDL_Event event, *e;e=&event;
    bool quit=false, ret=0, recordi_proverka = false, same_player=true;
    SDL_Surface *splash_screen=SDL_LoadBMP("me.bmp");
    if(splash_screen==nullptr)
    {
        cout<<"Error opening file"<<SDL_GetError();
    }
    menu.texture=SDL_CreateTextureFromSurface(menu.render, splash_screen);
    SDL_RenderCopy(menu.render, menu.texture, nullptr, nullptr);
    SDL_RenderPresent(menu.render);
    SDL_DestroyTexture(menu.texture);
    SDL_Delay(2000);
    player[i]=menu.EnterName();
    player[i]+=" - "; cout << "player[i] = " << player[i] << endl;
    samename=player[i];
    menu.PrintText();
    bool knopki_v_menu = true;
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(CatchTheBall.IsMouseInside(x, y, menu.StartRect) && knopki_v_menu )
                {
                    string results = CatchTheBall.play(menu.render);
                    if(same_player)
                    {
                        CatchTheBall.allPause = 0;
                        if (results == "")
                            player[i] = "";
                        else
                        {
                            player[i]=samename;
                            player[i]+=results;
                        }
                        menu.PrintText();
                    }
                    else
                    {
                        if (results == "")
                            player[i] = "";
                        else
                        {
                            player[i]+=results;
                        }
                        same_player=true;
                        menu.PrintText();
                    }
                    recordi_proverka = true;
                    cout << "player[i] = " << player[i] << endl;
                    tmp[i] = player[i];

                }
                else if(CatchTheBall.IsMouseInside(x, y, menu.RulesRect)  )
                {
                    menu.Rules();
                    knopki_v_menu = false;

                }
                else if(CatchTheBall.IsMouseInside(x, y, menu.ChangeRect) && knopki_v_menu )
                {
                    if(i!=10 && player[i] != "")
                        i++;
                    same_player=false;
                    player[i] = menu.EnterName();
                    player[i]+= " - ";
                    samename=player[i];
                    cout << "change i = " << i << endl;
                    cout << "player[i] = " << player[i] << endl;
                    in_count=0;
                    menu.PrintText();
                }
                else if(CatchTheBall.IsMouseInside(x, y, menu.RecordsRect) && knopki_v_menu )
                {
                    file.Clear();
                    //tmp[i] = player[i];
                    if(recordi_proverka)
                    {
                        file.BinFile(player);
                        menu.CreateSurfaceFromWidnow("records.bmp");
                        file.Start(menu.screen, menu.window);
                        //i++;
                        in_count++;
                        recordi_proverka=false;
                    }
                    else
                    {
                        if(in_count<1)
                        {
                            tmp[i]=" ";
                            file.BinFile(tmp);
                        }
                        else
                            file.BinFile(player);
                        cout << "tmp i = " << i << endl;
                        menu.CreateSurfaceFromWidnow("records.bmp");
                        file.Start(menu.screen, menu.window);
                    }
                    bool loop=false;
                    SDL_Event p;
                    while( !loop )
                    {
                        while(SDL_PollEvent(&p)!=0)
                        {
                            int a, b;
                            SDL_GetMouseState(&a, &b);
                            if(p.type==SDL_MOUSEBUTTONDOWN&&CatchTheBall.IsMouseInside(a, b, CatchTheBall.AddExit))
                            {
                                    loop=true;
                                    menu.PrintText();
                                    break;
                            }
                            else if (p.type==SDL_KEYDOWN)
                            {
                                switch(p.key.keysym.sym)
                                {
                                case SDLK_d:
                                    file.Clear();
                                    for(int n=0;n<11;n++)
                                    {
                                        player[n].clear();
                                        tmp[n].clear();
                                    }
                                    i = 0;
                                    menu.CreateSurfaceFromWidnow("records.bmp");
                                    break;
                                case SDLK_c:
                                    file.Convert();
                                    menu.CreateSurfaceFromWidnow("convert.bmp");
                                    //SDL_Delay(2000);
                                    break;
                                }
                            }

                        }
                    }
                }
                else if(CatchTheBall.IsMouseInside(x, y, menu.ExitRect) && knopki_v_menu )
                {
                    ret=1;
                }
                else if(CatchTheBall.IsMouseInside(x, y, menu.CloseRect)  )
                {
                    menu.PrintText();
                    knopki_v_menu = true;
                }
            }
            if(ret==1)
                quit=true;
        }
    }
    return 0;
}
