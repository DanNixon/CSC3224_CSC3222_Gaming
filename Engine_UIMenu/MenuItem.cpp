/**
 * @file
 * @author Dan Nixon
 */

#include "MenuItem.h"

#include <Alignment.h>
#include <RectangleMesh.h>

#include "IMenu.h"

using namespace Engine::Graphics;

namespace Engine
{
  namespace UIMenu
  {
    MenuItem::MenuItem(IMenu *menu, MenuItem *parent, const std::string &name)
      : TextPane(name, menu->textHeight(), menu->shader(), menu->font())
    {
      parent->addChild(*this);
      setText(name);

      Alignment_bitset align;
      align.set(Alignment::X_LEFT);
      align.set(Alignment::Y_BOTTOM);
      static_cast<RectangleMesh *>(m_mesh)->setAlignment(align);
    }

    MenuItem::~MenuItem()
    {
    }
  }
}