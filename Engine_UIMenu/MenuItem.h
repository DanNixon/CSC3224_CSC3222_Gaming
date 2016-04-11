/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_UIMENU_MENUITEM_H_
#define _ENGINE_UIMENU_MENUITEM_H_

#include <Engine_Graphics/TextPane.h>

namespace Engine
{
namespace UIMenu
{
  enum class MenuItemState;
  class IMenu;

  /**
   * @class MenuItem
   * @brief Represents an item on a menu.
   * @author Dan Nixon
   */
  class MenuItem : public Engine::Graphics::TextPane
  {
  public:
    MenuItem(IMenu *menu, SceneObject *parent, const std::string &name);
    virtual ~MenuItem();

    /**
     * @brief Gets the selection state of this menu item.
     * @return Selection state
     * @see MenuItem::setState
     */
    inline MenuItemState state() const
    {
      return m_state;
    }

    void setState(MenuItemState state);

    void setText(const std::string &str, bool layout = false);

  protected:
    IMenu *m_menu;         //!< Menu this item belongs to
    MenuItemState m_state; //!< Selection state of this item
  };
}
}

#endif
