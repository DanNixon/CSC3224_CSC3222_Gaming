/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_IMENU_H_
#define _ENGINE_UIMENU_IMENU_H_

#include <GraphicalScene.h>

#include <SDL_ttf.h>

#include <ShaderProgram.h>

#include "MenuItem.h"

namespace Engine
{
  namespace UIMenu
  {
    class IMenu : public Engine::Graphics::GraphicalScene
    {
    public:
      IMenu(TTF_Font *font, float height = 1.0f);
      virtual ~IMenu();

      Engine::Graphics::ShaderProgram *shader() const
      {
        return m_shaderProg;
      }

      TTF_Font *font() const
      {
        return m_font;
      }

      float textHeight() const
      {
        return m_textHeight;
      }

      virtual void layout() = 0;

    private:
      Engine::Graphics::ShaderProgram *m_shaderProg;
      TTF_Font *m_font;
      float m_textHeight;
    };
  }
}

#endif