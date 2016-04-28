/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_EDGESELECTIONPANE_H_
#define _SIMULATION_GRAPHICALPATHFINDER_EDGESELECTIONPANE_H_

#include <Engine_UIMenu/SoupMenu.h>

#include <Engine_Common/Game.h>
#include <Engine_Graphics/TextPane.h>

#include "PathFinder.h"

namespace Simulation
{
namespace GraphicalPathFinder
{
  class EdgeSelectionPane : public Engine::UIMenu::SoupMenu
  {
  public:
    EdgeSelectionPane(Engine::Common::Game *game, TTF_Font *font, float textSize);
    virtual ~EdgeSelectionPane();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    float m_margin;
    PathFinder *m_pathFinder;
    Engine::Graphics::TextPane *m_edgeName;
  };
}
}

#endif
