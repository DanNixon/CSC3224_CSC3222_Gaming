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
      : TextPane(name, menu->textHeight(), menu->shader(), menu->font(), TextMode::SHADED)
      , m_menu(menu)
  {
    parent->addChild(this);

    // Set alignment of text textured rectangle
    Alignment_bitset align;
    align.set(Alignment::X_LEFT);
    align.set(Alignment::Y_BOTTOM);
    static_cast<RectangleMesh *>(m_mesh)->setAlignment(align);

    // Default values
    setText(name);
    setTextColour(Colour(0.0f, 0.0f, 0.0f, 1.0f));
    setState(MenuItemState::NORMAL);
  }

  MenuItem::~MenuItem()
  {
  }

  void MenuItem::setState(MenuItemState state)
  {
    m_state = state;

    Colour bgColour = m_menu->itemColour(m_state);
    setBackgroundColour(bgColour);
  }
}
}