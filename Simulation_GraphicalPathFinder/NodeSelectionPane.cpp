/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "NodeSelectionPane.h"

#include <Engine_Graphics/RectangleMesh.h>

#include "PathFinder.h"

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::UIMenu;

namespace Simulation
{
namespace GraphicalPathFinder
{
  /**
   * @copydoc SelectionPane::SelectionPane
   */
  NodeSelectionPane::NodeSelectionPane(Game *game, TTF_Font *font, float textSize)
      : SelectionPane(game, font, textSize, Vector2(0.4f, 0.13f))
  {
    // Pick start node button
    MenuItem *pickStart = addNewItem(nullptr, "pick_start", "Pick Start");
    pickStart->setAlignment(GetAlignment(Alignment::Y_BOTTOM, Alignment::X_RIGHT));
    pickStart->setModelMatrix(Matrix4::Translation(Vector3(-m_margin, textSize + m_margin)));

    // Pick end node button
    MenuItem *pickEnd = addNewItem(nullptr, "pick_end", "Pick End");
    pickEnd->setAlignment(GetAlignment(Alignment::Y_BOTTOM, Alignment::X_LEFT));
    pickEnd->setModelMatrix(Matrix4::Translation(Vector3(m_margin, textSize + m_margin)));
  }

  NodeSelectionPane::~NodeSelectionPane()
  {
  }

  /**
  * @copydoc IMenu::handleMenuOptionSelection
  */
  void NodeSelectionPane::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    const std::string selectedName(item->name());
    // TODO
  }
}
}
