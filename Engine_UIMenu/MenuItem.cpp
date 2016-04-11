/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "MenuItem.h"

#include <Engine_Graphics/Alignment.h>
#include <Engine_Graphics/RectangleMesh.h>

#include "IMenu.h"

using namespace Engine::Graphics;

namespace Engine
{
namespace UIMenu
{
  /**
   * @brief Creates a new menu item.
   * @param menu Menu this item is a part of
   * @param parent Parent menu item
   * @param name Name of this item
   */
  MenuItem::MenuItem(IMenu *menu, SceneObject *parent, const std::string &name)
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

  /**
   * @brief Sets the selection state of this item.
   * @param state Selection state
   * @see MenuItem::state
   */
  void MenuItem::setState(MenuItemState state)
  {
    m_state = state;

    Colour bgColour = m_menu->itemColour(m_state);
    setBackgroundColour(bgColour);
  }

  /**
   * @copydoc TextPane::setText
   * @param layout If the layout should be updated after the text is changed
   */
  void MenuItem::setText(const std::string &str, bool layout)
  {
    TextPane::setText(str);

    if (layout)
      m_menu->layout();
  }
}
}
