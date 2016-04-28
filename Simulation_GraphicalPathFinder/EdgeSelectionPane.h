/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_EDGESELECTIONPANE_H_
#define _SIMULATION_GRAPHICALPATHFINDER_EDGESELECTIONPANE_H_

#include "SelectionPane.h"

namespace Simulation
{
namespace GraphicalPathFinder
{
  class EdgeSelectionPane : public SelectionPane
  {
  public:
    EdgeSelectionPane(Engine::Common::Game *game, TTF_Font *font, float textSize);
    virtual ~EdgeSelectionPane();

  protected:
    virtual void handleMenuOptionSelection(Engine::UIMenu::MenuItem *item);

  private:
    Engine::Graphics::TextPane *m_weightText;
    Engine::Graphics::TextPane *m_connectionText;
    Engine::Graphics::TextPane *m_costText;
  };
}
}

#endif
