/**
 * @file
 * @author Dan Nixon
 */

#include "TextRenderer.h"

#include <SDL_ttf.h>

namespace Engine
{
namespace Graphics
{
  TextRenderer::TextRenderer()
  {
    TTF_Init();
  }

  TextRenderer::~TextRenderer()
  {
    TTF_Quit();
  }

  void TextRenderer::drawString(SDL_Surface *screen, char *string, int size,
                                int x, int y, int fR, int fG, int fB, int bR,
                                int bG, int bB)
  {
    TTF_Font *font = TTF_OpenFont("ARIAL.TTF", size);
    SDL_Color foregroundColor = {fR, fG, fB};
    SDL_Color backgroundColor = {bR, bG, bB};
    SDL_Surface *textSurface =
        TTF_RenderText_Shaded(font, string, foregroundColor, backgroundColor);
    SDL_Rect textLocation = {x, y, 0, 0};
    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
  }
}
}