/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_PATHFINDER_H_
#define _SIMULATION_GRAPHICALPATHFINDER_PATHFINDER_H_

#include <Engine_Common/Game.h>

#include <Engine_Common/Scene.h>

namespace Simulation
{
namespace GraphicalPathFinder
{
  /**
   * @class PathFinder
   * @brief Game application for a graphical path finder.
   * @author Dan Nixon
   */
  class PathFinder : public Engine::Common::Game
  {
  public:
    PathFinder();
    ~PathFinder();

  protected:
    int gameStartup();
    void gameLoop(Uint8 id, float dtMilliSec);
    void gameShutdown();

  private:
    Uint8 m_graphicsLoop; //!< Graphics update loop ID

    Engine::Common::Scene *m_scene; //!< Scene containing path representation
  };
}
}

#endif
