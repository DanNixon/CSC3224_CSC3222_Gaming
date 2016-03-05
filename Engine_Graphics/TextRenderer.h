/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_TEXTRENDERER_H_
#define _ENGINE_GRAPHICS_TEXTRENDERER_H_

#include <SDL/SDL.h>

namespace Engine
{
  namespace Graphics
  {
    class TextRenderer
    {
    public:
      TextRenderer();
      virtual ~TextRenderer();

      void drawString(SDL_Surface* screen,
        char* string,
        int size,
        int x, int y,
        int fR, int fG, int fB,
        int bR, int bG, int bB);
    };
  }
}

#endif