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
  NodeSelectionPane::NodeSelectionPane(Game *game, TTF_Font *font, float textSize, PathFinder::NodeMap::iterator begin,
                                       PathFinder::NodeMap::iterator end)
      : SelectionPane(game, font, textSize, Vector2(0.4f, 0.13f))
      , m_nodesBegin(begin)
      , m_nodesEnd(end)
      , m_selectedNodeIt(begin)
  {
    // Pick start node button
    MenuItem *pickStart = addNewItem(nullptr, "pick_start", "Pick Start");
    pickStart->setAlignment(GetAlignment(Alignment::Y_BOTTOM, Alignment::X_RIGHT));
    pickStart->setModelMatrix(Matrix4::Translation(Vector3(-m_margin, textSize + m_margin)));

    // Pick end node button
    MenuItem *pickEnd = addNewItem(nullptr, "pick_end", "Pick End");
    pickEnd->setAlignment(GetAlignment(Alignment::Y_BOTTOM, Alignment::X_LEFT));
    pickEnd->setModelMatrix(Matrix4::Translation(Vector3(m_margin, textSize + m_margin)));

    // Set initial selected node
    updateDisplay();
  }

  NodeSelectionPane::~NodeSelectionPane()
  {
  }

  void NodeSelectionPane::selectNode(PathFinder::NodeMap::iterator it)
  {
    m_selectedNodeIt = it;

    updateDisplay();

    // Update graph
    m_pathFinder->setViewMode(m_pathFinder->viewMode());
  }

  void NodeSelectionPane::updateDisplay()
  {
    // Update name
    m_name->setText(m_selectedNodeIt->first->id());
  }

  /**
  * @copydoc IMenu::handleMenuOptionSelection
  */
  void NodeSelectionPane::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    if (item == m_previous)
    {
      if (m_selectedNodeIt == m_nodesBegin)
        m_selectedNodeIt = m_nodesEnd;

      --m_selectedNodeIt;

      selectNode(m_selectedNodeIt);
    }
    else if (item == m_next)
    {
      ++m_selectedNodeIt;

      if (m_selectedNodeIt == m_nodesEnd)
        m_selectedNodeIt == m_nodesBegin;

      selectNode(m_selectedNodeIt);
    }
    else if (item->name() == "pick_start")
    {
      m_pathFinder->setStartNode(m_selectedNodeIt);
    }
    else if (item->name() == "pick_end")
    {
      m_pathFinder->setEndNode(m_selectedNodeIt);
    }
  }
}
}
