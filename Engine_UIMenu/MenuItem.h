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
    class IMenu;

    class MenuItem : public Engine::Graphics::TextPane
    {
    public:
      MenuItem(IMenu *menu, MenuItem *parent, const std::string &name);
      virtual ~MenuItem();
    };
  }
}

#endif