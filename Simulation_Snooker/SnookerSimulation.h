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

#include <SImulation_AI/StateMachine.h>
#include <Simulation_Physics/Entity.h>
#include <Simulation_Physics/PhysicsSimulation.h>

#include "Ball.h"
#include "OptionsMenu.h"
#include "Table.h"

namespace Simulation
{
namespace Snooker
{
  enum class SnookerBalls
  {
    ALL = -2,
    CUE_BALL = -1,
    ALL_COLOURS = 0,
    RED = 1,
    YELLOW = 2,
    GREEN = 3,
    BROWN = 4,
    BLUE = 5,
    PINK = 6,
    BLACK = 7
  };

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

    void placeBalls(SnookerBalls b = SnookerBalls::ALL);

  protected:
    int gameStartup();
    void gameLoop(Uint8 id, float dtMilliSec);
    void gameShutdown();

  public:
    Simulation::Physics::PhysicsSimulation physics;
    Engine::Input::IControlScheme *controls;
    Simulation::AI::StateMachine *fsm;

    Ball *balls[NUM_BALLS];
    Engine::Graphics::RenderableObject *shotAimLine;

  private:
    friend class SnookerControls;

    Uint8 m_graphicsLoop;
    Uint8 m_physicsLoop;
    Uint8 m_controlLoop;
    Uint8 m_profileLoop;

    Engine::Common::Scene *m_scene;
    Engine::Common::Scene *m_ui;
    OptionsMenu *m_menu;

    Table *m_table;

    TTF_Font *m_fontLarge;
    TTF_Font *m_fontMedium;
    Engine::Graphics::ShaderProgram *m_uiShader;
    Engine::Graphics::TextPane *m_profileText;
  };
}
}

#endif