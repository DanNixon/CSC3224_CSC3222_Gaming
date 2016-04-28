/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "EdgeSelectionPane.h"

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
  EdgeSelectionPane::EdgeSelectionPane(Game *game, TTF_Font *font, float textSize)
      : SelectionPane(game, font, textSize, Vector2(0.4f, 0.24f))
  {
    const float offset(textSize + m_margin);

    // Connections
    m_connectionText = newTextPane("connection", GetAlignment(Alignment::Y_BOTTOM, Alignment::X_CENTRE));
    m_connectionText->setModelMatrix(Matrix4::Translation(Vector3(0.0f, offset)));
    m_connectionText->setText("a - b");

    // Increase weight button
    MenuItem *increaseWeight = addNewItem(nullptr, "increase_weight", "+");
    increaseWeight->setAlignment(GetAlignment(Alignment::Y_BOTTOM, Alignment::X_LEFT));
    increaseWeight->setModelMatrix(Matrix4::Translation(Vector3(-0.19f, 2.0f * offset)));

    // Decrease weight button
    MenuItem *decreaseWeight = addNewItem(nullptr, "decrease_weight", "-");
    decreaseWeight->setAlignment(GetAlignment(Alignment::Y_BOTTOM, Alignment::X_RIGHT));
    decreaseWeight->setModelMatrix(Matrix4::Translation(Vector3(0.19f, 2.0f * offset)));

    // Weight
    m_weightText = newTextPane("weight", GetAlignment(Alignment::Y_BOTTOM, Alignment::X_CENTRE));
    m_weightText->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 2.0f * offset)));
    m_weightText->setText("w = 0.0");

    // Cost
    m_costText = newTextPane("cost", GetAlignment(Alignment::Y_BOTTOM, Alignment::X_CENTRE));
    m_costText->setModelMatrix(Matrix4::Translation(Vector3(0.0f, offset * 3.0f)));
    m_costText->setText("cost = 0.0");
  }

  EdgeSelectionPane::~EdgeSelectionPane()
  {
  }

  /**
   * @copydoc IMenu::handleMenuOptionSelection
   */
  void EdgeSelectionPane::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    const std::string selectedName(item->name());
    // TODO
  }
}
}
