/**
 * @file
 * @author Dan Nixon
 */

#include "MenuItem.h"

#include "IMenu.h"

namespace Engine
{
  namespace UIMenu
  {
    MenuItem::MenuItem(IMenu *menu, MenuItem *parent, const std::string &name)
      : TextPane(name, menu->textHeight(), menu->shader(), menu->font())
    {
      parent->addChild(*this);
      setText(name);
    }

    MenuItem::~MenuItem()
    {
    }
  }
}