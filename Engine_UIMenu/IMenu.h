/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_IMENU_H_
#define _ENGINE_UIMENU_IMENU_H_

#include <GraphicalScene.h>

#include <map>

#include <SDL_ttf.h>

#include <Colour.h>
#include <ShaderProgram.h>

#include "MenuItem.h"

namespace Engine
{
namespace UIMenu
{
  enum class MenuItemState
  {
    NORMAL,
    HOVER,
    SELECTED,
    DISABLED
  };

  class IMenu : public Engine::Graphics::GraphicalScene
  {
  public:
    IMenu(TTF_Font *font, float height = 0.1f);
    virtual ~IMenu();

    inline Engine::Graphics::ShaderProgram *shader() const
    {
      return m_shaderProg;
    }

    inline TTF_Font *font() const
    {
      return m_font;
    }

    inline float textHeight() const
    {
      return m_textHeight;
    }

    inline Engine::Graphics::Colour itemColour(MenuItemState state)
    {
      return m_itemColours[state];
    }

    Engine::Maths::Vector3 position() const;
    void setPosition(const Engine::Maths::Vector3 &position);

    virtual void layout() = 0;

  protected:
    Engine::Graphics::ShaderProgram *m_shaderProg;
    TTF_Font *m_font;
    float m_textHeight;
    std::map<MenuItemState, Engine::Graphics::Colour> m_itemColours;
  };
}
}

#endif