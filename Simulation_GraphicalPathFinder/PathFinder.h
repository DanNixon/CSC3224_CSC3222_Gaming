/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_GRAPHICALPATHFINDER_PATHFINDER_H_
#define _SIMULATION_GRAPHICALPATHFINDER_PATHFINDER_H_

#include <Engine_Common/Game.h>

#include <map>

#include <Engine_Common/Scene.h>
#include <Engine_Graphics/RenderableObject.h>
#include <Engine_Graphics/ShaderProgram.h>

#include <Simulation_PathFinding/Edge.h>
#include <Simulation_PathFinding/Node.h>

#include "Controls.h"

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
    Uint8 m_controlLoop;  //!< Control update loop ID

    Engine::Graphics::ShaderProgram *m_colShader; //!< Shader based on fragment colour
    Engine::Common::Scene *m_scene;               //!< Scene containing path representation
    Controls *m_controls;                         //!< Control scheme

    std::map<Simulation::PathFinding::Node *, Engine::Graphics::RenderableObject *> m_nodes;
    std::map<Simulation::PathFinding::Edge *, Engine::Graphics::RenderableObject *> m_edges;

    int m_currentNodeIndex;
  };
}
}

#endif
