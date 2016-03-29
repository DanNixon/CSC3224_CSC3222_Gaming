/**
 * @file
 * @author Dan Nixon
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

  protected:
    IMenu *m_menu;         //!< Menu this item belongs to
    std::string m_text;    //!< Text displayed on this item
    MenuItemState m_state; //!< Selection state of this item
  };
}
}

#endif
