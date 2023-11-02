#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <string.h>
#include <SDL.h>
using namespace std;
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

#endif // FILE_H
