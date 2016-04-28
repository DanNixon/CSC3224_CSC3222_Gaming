/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "OptionsMenu.h"

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
    m_viewMenu = addNewItem(nullptr, "view", "View");
    m_pickMenu = addNewItem(nullptr, "pick", "Pick");
    addNewItem(nullptr, "find_path", "Find Path");

    // View menu
    addNewItem(m_viewMenu, "graph", "Simple Graph");
    addNewItem(m_viewMenu, "weights", "Weights");
    addNewItem(m_viewMenu, "open_list", "Open List");
    addNewItem(m_viewMenu, "closed_list", "Closed List");
    addNewItem(m_viewMenu, "path", "Path");

    // Pick menu
    addNewItem(m_pickMenu, "nodes", "Nodes");
    addNewItem(m_pickMenu, "edges", "Edges");
  }

  OptionsMenu::~OptionsMenu()
  {
  }

  /**
   * @copydoc IMenu::handleMenuOptionSelection
   */
  void OptionsMenu::handleMenuOptionSelection(Engine::UIMenu::MenuItem *item)
  {
    const std::string selectedName(item->name());

    if (selectedName == "exit")
    {
      m_game->exit();
    }
    else if (item->parent() == m_viewMenu)
    {
      ViewMode_bitset mode = m_pathFinder->viewMode();

      // Reset view to showing graph only
      if (selectedName == "graph")
        mode = ViewMode_bitset();

      // Toggle features
      else if (selectedName == "weights")
        mode.flip(ViewMode::WEIGHTS);
      else if (selectedName == "open_list")
        mode.flip(ViewMode::OPEN_LIST);
      else if (selectedName == "closed_list")
        mode.flip(ViewMode::CLOSED_LIST);
      else if (selectedName == "path")
        mode.flip(ViewMode::PATH);

      m_pathFinder->setViewMode(mode);
    }
    else if (item->parent() == m_pickMenu)
    {
      // TODO
    }
    if (selectedName == "find_path")
    {
      // TODO
    }
  }
}
}
