/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_TEXTPANE_H_
#define _ENGINE_GRAPHICS_TEXTPANE_H_

#include "RenderableObject.h"

#include <SDL_ttf.h>

namespace Engine
{
namespace Graphics
{
  class TextPane : public RenderableObject
  {
  public:
    TextPane(float height, ShaderProgram *s, TTF_Font *font);
    virtual ~TextPane();

    void setText(const std::string &str);
    void setColour(const Engine::Graphics::Colour &col);

  private:
    const float m_height;
    TTF_Font *m_font;
    Engine::Graphics::Colour m_colour;
  };
}
}

#endif