/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_MENUITEM_H_
#define _ENGINE_UIMENU_MENUITEM_H_

#include <TextPane.h>

#include <vector>

namespace Engine
{
  namespace UIMenu
  {
    enum class MenuItemState;
    class IMenu;

    class MenuItem : public Engine::Graphics::TextPane
    {
    public:
      MenuItem(IMenu *menu, MenuItem *parent, const std::string &name);
      virtual ~MenuItem();

      MenuItemState state() const
      {
        return m_state;
      }

      void setState(MenuItemState state);

    protected:
      IMenu *m_menu;
      MenuItemState m_state;
    };
  }
}

#endif