#include "file.h"
#include <iostream>
#include <fstream>
#include <SDL_ttf.h>
using namespace std;
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
