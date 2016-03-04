#pragma once

#include <SDL/SDL.h>

class TextUtils
{
public:
  void TextUtils::DrawString(SDL_Surface* screen,
    char* string,
    int size,
    int x, int y,
    int fR, int fG, int fB,
    int bR, int bG, int bB);
};