/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_SNOOKERSIMULATION_H_
#define _SIMULATION_SNOOKER_SNOOKERSIMULATION_H_

#include <Engine_Common/Game.h>

#include <SDL_ttf.h>

#include <Engine_Common/Scene.h>
#include <Engine_Graphics/RenderableObject.h>
#include <Engine_Graphics/ShaderProgram.h>
#include <Engine_Graphics/TextPane.h>
#include <Engine_Input/IControlScheme.h>

#include <Simulation_Physics/Entity.h>
#include <Simulation_Physics/PhysicsUpdate.h>

#include "Ball.h"
#include "Table.h"

namespace Simulation
{
namespace Snooker
{
  /**
   * @class SnookerSimulation
   * @brief Game application for the snooker simulation.
   * @author Dan Nixon
   */
  class SnookerSimulation : public Engine::Common::Game
  {
  public:
    /**
     * @brief Number of snooker balls.
     */
    static const int NUM_BALLS = 22;

    SnookerSimulation();
    ~SnookerSimulation();

  protected:
    int gameStartup();
    void gameLoop(Uint8 id, float dtMilliSec);
    void gameShutdown();

    void updateControl();

  private:
    Uint8 m_graphicsLoop;
    Uint8 m_physicsLoop;
    Uint8 m_controlLoop;
    Uint8 m_profileLoop;

    Engine::Input::IControlScheme *m_controls;

    Engine::Common::Scene *m_scene;
    Engine::Common::Scene *m_ui;

    Table *m_table;
    Ball *m_balls[NUM_BALLS];

    Simulation::Physics::Entity::EntityPtrList m_entities;
    Simulation::Physics::PhysicsUpdate m_physics;

    TTF_Font *m_fontLarge;
    TTF_Font *m_fontMedium;
    Engine::Graphics::ShaderProgram *m_uiShader;
    Engine::Graphics::TextPane *m_profileGraphics;
    Engine::Graphics::TextPane *m_profilePhysics;

    Engine::Maths::Vector2 *m_mouseStartPosition;
    Engine::Graphics::RenderableObject *m_shotAimLine;
  };
}
}

#endif