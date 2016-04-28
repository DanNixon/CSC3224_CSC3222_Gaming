/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_NODESELECTIONPANE_H_
#define _SIMULATION_GRAPHICALPATHFINDER_NODESELECTIONPANE_H_

#include "SelectionPane.h"

namespace Simulation
{
namespace GraphicalPathFinder
{
  class NodeSelectionPane : public SelectionPane
  {
  public:
    NodeSelectionPane(Engine::Common::Game *game, TTF_Font *font, float textSize);
    virtual ~NodeSelectionPane();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);
  };
}
}

#endif
