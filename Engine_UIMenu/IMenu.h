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
#include <MouseHandler.h>
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
    DISABLED
  };

  class IMenu : public Engine::Graphics::GraphicalScene, public Engine::Input::MouseHandler
  {
  public:
    IMenu(TTF_Font *font, int screenWidth, int screenHeight, float textHeight = 0.1f);
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

    bool visible() const;
    virtual void show();
    virtual void hide();

    virtual void layout() = 0;

  protected:
    virtual void handleButton(const SDL_MouseButtonEvent &e);
    virtual void handleMotion(const SDL_MouseMotionEvent &e);

    bool checkMouseOver(const Engine::Maths::Vector3 &mousePos, Engine::Common::SceneObject *node);

  protected:
    Engine::Graphics::ShaderProgram *m_shaderProg;
    TTF_Font *m_font;
    int m_screenWidth;
    int m_screenHeight;
    float m_textHeight;
    std::map<MenuItemState, Engine::Graphics::Colour> m_itemColours;
    MenuItem *m_currentMouseOver;
  };
}
}

#endif