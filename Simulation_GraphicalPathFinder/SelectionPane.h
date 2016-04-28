/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_SELECTIONPANE_H_
#define _SIMULATION_GRAPHICALPATHFINDER_SELECTIONPANE_H_

#include <Engine_UIMenu/SoupMenu.h>

#include <Engine_Common/Game.h>
#include <Engine_Graphics/TextPane.h>

#include "PathFinder.h"

namespace Simulation
{
namespace GraphicalPathFinder
{
  class SelectionPane : public Engine::UIMenu::SoupMenu
  {
  public:
    SelectionPane(Engine::Common::Game *game, TTF_Font *font, float textSize, const Engine::Maths::Vector2 &bgSize);
    virtual ~SelectionPane();

  protected:
    Engine::Graphics::TextPane *newTextPane(const std::string &name, Engine::Graphics::Alignment_bitset alignment);

  protected:
    float m_margin;
    Engine::Graphics::Colour m_backgroundColour;

    Engine::UIMenu::MenuItem *m_previous;
    Engine::UIMenu::MenuItem *m_next;

    PathFinder *m_pathFinder;
    Engine::Graphics::TextPane *m_name;
  };
}
}

#endif
