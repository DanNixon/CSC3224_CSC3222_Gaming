#include "TextUtils.h"

#include <SDL_ttf.h>

// TTF_Init() must be called before using this function.
// Remember to call TTF_Quit() when done.
void TextUtils::DrawString(SDL_Surface* screen,
    char* string,
    int size,
    int x, int y,
    int fR, int fG, int fB,
    int bR, int bG, int bB)
  {
    TTF_Font* font = TTF_OpenFont("ARIAL.TTF", size);
    SDL_Color foregroundColor = { fR, fG, fB };
    SDL_Color backgroundColor = { bR, bG, bB };
    SDL_Surface* textSurface = TTF_RenderText_Shaded(font, string,
      foregroundColor, backgroundColor);
    SDL_Rect textLocation = { x, y, 0, 0 };
    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

}