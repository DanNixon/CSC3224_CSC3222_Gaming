/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_OPTIONSMENU_H_
#define _SIMULATION_GRAPHICALPATHFINDER_OPTIONSMENU_H_

#include <Engine_UIMenu/TopBarMenu.h>

#include <Engine_Common/Game.h>

#include "ViewMode.h"

namespace Simulation
{
namespace GraphicalPathFinder
{
  class PathFinder;

  /**
   * @class OptionsMenu
   * @brief Menu used to display path finder options.
   * @author Dan Nixon
   */
  class OptionsMenu : public Engine::UIMenu::TopBarMenu
  {
  public:
    OptionsMenu(Engine::Common::Game *game, TTF_Font *font, float textSize);
    virtual ~OptionsMenu();

    void updateViewMenu(ViewMode_bitset mode);

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    PathFinder *m_pathFinder;

    Engine::UIMenu::MenuItem *m_viewMenu;
    Engine::UIMenu::MenuItem *m_pickMenu;

    Engine::UIMenu::MenuItem *m_viewWeights;
    Engine::UIMenu::MenuItem *m_viewStaticCosts;
    Engine::UIMenu::MenuItem *m_viewCosts;
    Engine::UIMenu::MenuItem *m_viewOpenList;
    Engine::UIMenu::MenuItem *m_viewClosedList;
    Engine::UIMenu::MenuItem *m_viewPath;
  };
}
}

#endif
