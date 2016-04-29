/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "OptionsMenu.h"

#include "EdgeSelectionPane.h"
#include "NodeSelectionPane.h"
#include "PathFinder.h"

using namespace Engine::Common;
using namespace Engine::UIMenu;
using namespace Engine::Input;

namespace Simulation
{
namespace GraphicalPathFinder
{
  /**
   * @copydoc TopBarMenu::TopBarMenu
   */
  OptionsMenu::OptionsMenu(Game *game, TTF_Font *font, float textSize)
      : TopBarMenu(game, font, textSize)
      , m_pathFinder(static_cast<PathFinder *>(game))
  {
    // Root menu
    addNewItem(nullptr, "exit", "Exit");
    addNewItem(nullptr, "reset", "Reset");
    m_viewMenu = addNewItem(nullptr, "view", "View");
    m_pickMenu = addNewItem(nullptr, "pick", "Pick");
    addNewItem(nullptr, "find_path", "Find Path");

    // View menu
    addNewItem(m_viewMenu, "graph", "Simple Graph");
    m_viewWeights = addNewItem(m_viewMenu, "weights", "Weights (off)");
    m_viewStaticCosts = addNewItem(m_viewMenu, "static_costs", "Static Costs (off)");
    m_viewCosts = addNewItem(m_viewMenu, "costs", "Weighted Costs (off)");
    m_viewOpenList = addNewItem(m_viewMenu, "open_list", "Open List (off)");
    m_viewClosedList = addNewItem(m_viewMenu, "closed_list", "Closed List (off)");
    m_viewPath = addNewItem(m_viewMenu, "path", "Path (off)");

    // Pick menu
    addNewItem(m_pickMenu, "nodes", "Nodes");
    addNewItem(m_pickMenu, "edges", "Edges");
  }

  OptionsMenu::~OptionsMenu()
  {
  }

  void OptionsMenu::updateViewMenu(ViewMode_bitset mode)
  {
    m_viewWeights->setText(mode.test(ViewMode::WEIGHTS) ? "Weights (on)" : "Weights (off)");
    m_viewStaticCosts->setText(mode.test(ViewMode::STATIC_COSTS) ? "Static Costs (on)" : "Static Costs (off)");
    m_viewCosts->setText(mode.test(ViewMode::COSTS) ? "Costs (on)" : "Costs (off)");
    m_viewOpenList->setText(mode.test(ViewMode::OPEN_LIST) ? "Open List (on)" : "Open List (off)");
    m_viewClosedList->setText(mode.test(ViewMode::CLOSED_LIST) ? "Closed List (on)" : "Closed List (off)");
    m_viewPath->setText(mode.test(ViewMode::PATH) ? "Path (on)" : "Path (off)");
  }

  /**
   * @copydoc IMenu::handleMenuOptionSelection
   */
  void OptionsMenu::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    const std::string selectedName(item->name());

    // Hnadle exit
    if (selectedName == "exit")
    {
      m_game->exit();
    }
    // Handle path finder state reset
    // (not really an important option, here because it can be)
    else if (selectedName == "reset")
    {
      // Reset path finder state
      m_pathFinder->m_finder->reset();

      // Reset view mode
      m_pathFinder->setViewMode();
    }
    // Handle view modes
    else if (item->parent() == m_viewMenu)
    {
      ViewMode_bitset mode = m_pathFinder->viewMode();

      // Reset view to showing graph only
      if (selectedName == "graph")
        mode = ViewMode_bitset();

      // Toggle features
      else if (selectedName == "weights")
        mode.flip(ViewMode::WEIGHTS);
      else if (selectedName == "static_costs")
        mode.flip(ViewMode::STATIC_COSTS);
      else if (selectedName == "costs")
        mode.flip(ViewMode::COSTS);
      else if (selectedName == "open_list")
        mode.flip(ViewMode::OPEN_LIST);
      else if (selectedName == "closed_list")
        mode.flip(ViewMode::CLOSED_LIST);
      else if (selectedName == "path")
        mode.flip(ViewMode::PATH);

      m_pathFinder->setViewMode(mode);
    }
    // Handle feature selection
    else if (item->parent() == m_pickMenu)
    {
      IMenu *selected = nullptr;
      IMenu *other = nullptr;

      // Select correct menu
      if (selectedName == "nodes")
      {
        selected = m_pathFinder->m_nodeSelection;
        other = m_pathFinder->m_edgeSelection;
      }
      else if (selectedName == "edges")
      {
        selected = m_pathFinder->m_edgeSelection;
        other = m_pathFinder->m_nodeSelection;
      }

      // Update menu visiblity
      other->hide();
      if (selected->visible())
        selected->hide();
      else
        selected->show();
    }
    // Handle start path finding
    if (selectedName == "find_path")
    {
      m_pathFinder->runPathFinding();
    }
  }
}
}
