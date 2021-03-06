/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_TEXTPANE_H_
#define _ENGINE_GRAPHICS_TEXTPANE_H_

#include "RenderableObject.h"

#include <SDL_ttf.h>

#include "Alignment.h"

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
    TextPane(const std::string &name, float height, ShaderProgram *s, TTF_Font *font,
             TextMode mode = TextMode::BLENDED);
    virtual ~TextPane();

    void setText(const std::string &str);
    void setAlignment(Alignment_bitset alignment);
    void setTextColour(const Engine::Graphics::Colour &col);
    void setBackgroundColour(const Engine::Graphics::Colour &col);

    void redraw();

  private:
    const float m_height;                //!< Height of the text
    TTF_Font *m_font;                    //!< Text font
    TextMode m_mode;                     //!< Text rendering mode
    std::string m_text;                  //!< Displayed text
    Engine::Graphics::Colour m_fgColour; //!< Text colour
    Engine::Graphics::Colour m_bgColour; //!< Background colour
  };
}
}

#endif
