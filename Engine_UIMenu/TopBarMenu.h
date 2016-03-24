/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_TOPBARMENU_H_
#define _ENGINE_UIMENU_TOPBARMENU_H_

#include "IMenu.h"

namespace Engine
{
namespace UIMenu
{
  /**
   * @class TopBarMenu
   * @brief A menu that is designed to go at the top of a screen.
   * @author Dan Nixon
   *
   * A main set of options which have their children arranged in a drop down
   * menu below them, then in drop down menus to the right of the selected
   * option.
   */
  class TopBarMenu : public IMenu
  {
  public:
    TopBarMenu(Engine::Common::Game *game, TTF_Font *font, float textHeight = 0.1f);
    virtual ~TopBarMenu();

    /**
     * @brief Gets the margin around menu items.
     * @return Margin
     */
    inline Engine::Maths::Vector2 margin() const
    {
      return m_margin;
    }

    /**
     * @brief Sets the margin around menu items.
     * @param margin Margin
     */
    void setMargin(const Engine::Maths::Vector2 &margin)
    {
      m_margin = margin;
    }

    virtual void show();
    virtual void layout();

  protected:
    void layoutChildRecursive(Engine::Graphics::RenderableObject *item, unsigned int level);

  private:
    Engine::Maths::Vector2 m_margin; //!< Margin around menu items
  };
}
}

#endif
