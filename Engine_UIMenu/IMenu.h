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
  /**
   * @brief Represents a selection state for a MenuItem.
   */
  enum class MenuItemState
  {
    NORMAL,
    HOVER,
    DISABLED
  };

  /**
   * @class IMenu
   * @brief Abstract class for a menu layout.
   * @author Dan Nixon
   */
  class IMenu : public Engine::Graphics::GraphicalScene, public Engine::Input::MouseHandler
  {
  public:
    IMenu(TTF_Font *font, int screenWidth, int screenHeight, float textHeight = 0.1f);
    virtual ~IMenu();

    /**
     * @brief Gets the shader program used to render the menu.
     * @return Shader program
     */
    inline Engine::Graphics::ShaderProgram *shader() const
    {
      return m_shaderProg;
    }

    /**
     * @brief Gets the font used to render menu text.
     * @return Text font
     */
    inline TTF_Font *font() const
    {
      return m_font;
    }

    /**
     * @brief Gets the preset text height.
     * @return Text height
     */
    inline float textHeight() const
    {
      return m_textHeight;
    }

    /**
     * @brief Gets the background colour of a MenuItem in a given state.
     * @param state Item state
     * @return Colour for state
     */
    inline Engine::Graphics::Colour itemColour(MenuItemState state)
    {
      return m_itemColours[state];
    }

    Engine::Maths::Vector3 position() const;
    void setPosition(const Engine::Maths::Vector3 &position);

    bool visible() const;
    virtual void show();
    virtual void hide();

    MenuItem *addNewItem(MenuItem *parent, const std::string &name, const std::string &text = std::string());

    /**
     * @brief Sets the layout of each MenuItem in the tree.
     */
    virtual void layout() = 0;

  protected:
    virtual void handleButton(const SDL_MouseButtonEvent &e);
    virtual void handleMotion(const SDL_MouseMotionEvent &e);

    bool checkMouseOver(const Engine::Maths::Vector3 &mousePos, Engine::Common::SceneObject *node);

    /**
     * @brief Handles the selection of a menu item.
     * @param item Selected item
     */
    virtual void handleMenuOptionSelection(MenuItem *item) = 0;

  protected:
    Engine::Graphics::ShaderProgram *m_shaderProg;                      //!< Shader program used for rendering menu
    TTF_Font *m_font;                                                   //!< Font used for rendering menu text
    int m_screenWidth;                                                  //!< Width of the screen in pixels
    int m_screenHeight;                                                 //!< Height of the screen in pixels
    float m_textHeight;                                                 //!< Height of the text
    std::map<MenuItemState, Engine::Graphics::C / olour> m_itemColours; //!< Mapping of item state to colour
    MenuItem *m_currentMouseOver; //!< Pointer to the item currently under the cursor
  };
}
}

#endif
