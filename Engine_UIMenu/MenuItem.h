/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_MENUITEM_H_
#define _ENGINE_UIMENU_MENUITEM_H_

#include <TextPane.h>

namespace Engine
{
namespace UIMenu
{
  enum class MenuItemState;
  class IMenu;

  class MenuItem : public Engine::Graphics::TextPane
  {
  public:
    MenuItem(IMenu *menu, SceneObject *parent, const std::string &name);
    virtual ~MenuItem();

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