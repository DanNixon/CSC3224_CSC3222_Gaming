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
using namespace Simulation::PathFinding;

namespace Simulation
{
namespace GraphicalPathFinder
{
  const float EdgeSelectionPane::DELTA_WEIGHT = 0.01f;

  /**
   * @copydoc SelectionPane::SelectionPane
   */
  EdgeSelectionPane::EdgeSelectionPane(Game *game, TTF_Font *font, float textSize, PathFinder::EdgeMap::iterator begin,
                                       PathFinder::EdgeMap::iterator end)
      : SelectionPane(game, font, textSize, Vector2(0.4f, 0.24f))
      , m_edgesBegin(begin)
      , m_edgesEnd(end)
      , m_selectedEdgeIt(begin)
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

    // Set initial selected edge
    updateDisplay();
  }

  EdgeSelectionPane::~EdgeSelectionPane()
  {
  }

  void EdgeSelectionPane::selectEdge(PathFinder::EdgeMap::iterator it)
  {
    m_selectedEdgeIt = it;

    updateDisplay();

    // Update graph
    m_pathFinder->setViewMode(m_pathFinder->viewMode());
  }

  void EdgeSelectionPane::updateDisplay()
  {
    Edge *edge = m_selectedEdgeIt->first;

    // Update name
    m_name->setText(edge->id());

    // Update connection
    std::string connectionStr = edge->nodeA()->id() + " - " + edge->nodeB()->id();
    m_connectionText->setText(connectionStr);

    // Update weight
    std::string weightStr = "w = " + std::to_string(edge->weight());
    m_weightText->setText(weightStr);

    // Update cost
    std::string costStr = "Cost = " + std::to_string(edge->staticCost());
    m_costText->setText(costStr);
  }

  /**
   * @copydoc IMenu::handleMenuOptionSelection
   */
  void EdgeSelectionPane::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    Edge *edge = m_selectedEdgeIt->first;

    if (item == m_previous)
    {
      if (m_selectedEdgeIt == m_edgesBegin)
        m_selectedEdgeIt = m_edgesEnd;

      --m_selectedEdgeIt;

      selectEdge(m_selectedEdgeIt);
    }
    else if (item == m_next)
    {
      ++m_selectedEdgeIt;

      if (m_selectedEdgeIt == m_edgesEnd)
        m_selectedEdgeIt == m_edgesBegin;

      selectEdge(m_selectedEdgeIt);
    }
    else if (item->name() == "increase_weight")
    {
      edge->setWeight(edge->weight() + DELTA_WEIGHT);

      updateDisplay();
    }
    else if (item->name() == "decrease_weight")
    {
      edge->setWeight(edge->weight() - DELTA_WEIGHT);

      updateDisplay();
    }
  }
}
}
