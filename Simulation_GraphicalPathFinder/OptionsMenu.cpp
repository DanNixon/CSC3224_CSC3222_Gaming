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
    addNewItem(m_viewMenu, "graph", "Graph");
    addNewItem(m_viewMenu, "weights", "Weights");
    addNewItem(m_viewMenu, "open_ist", "Open List");
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
    if (item->name() == "exit")
    {
      m_game->exit();
    }

    // TODO
  }
}
}
