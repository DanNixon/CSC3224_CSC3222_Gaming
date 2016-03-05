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
  /**
   * @class TextPane
   * @brief Used for drawing text along an axis aligned plane.
   * @author Dan Nixon
   */
  class TextPane : public RenderableObject
  {
  public:
    TextPane(float height, ShaderProgram *s, TTF_Font *font);
    virtual ~TextPane();

    void setText(const std::string &str);
    void setColour(const Engine::Graphics::Colour &col);

  private:
    const float m_height;              //!< Height of the text
    TTF_Font *m_font;                  //!< Text font
    Engine::Graphics::Colour m_colour; //!< Text colour
  };
}
}

#endif
