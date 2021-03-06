/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
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

#include <Simulation_AI/StateMachine.h>
#include <Simulation_Physics/Entity.h>
#include <Simulation_Physics/PhysicsSimulation.h>

#include "Ball.h"
#include "OptionsMenu.h"
#include "Table.h"

namespace Simulation
{
namespace Snooker
{
  /**
   * @enum SnookerBalls
   * @brief Enumeration of snooker balls, underlaying type denotes number of
   *        points.
   */
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

    void resetBalls(SnookerBalls b = SnookerBalls::ALL);

  protected:
    int gameStartup();
    void gameLoop(Uint8 id, float dtMilliSec);
    void gameShutdown();

  public:
    Simulation::Physics::PhysicsSimulation physics; //!< Physical simulation
    Engine::Input::IControlScheme *controls;        //!< Control scheme
    Simulation::AI::StateMachine *fsm;              //!< State machine
    OptionsMenu *menu;                              //!< Option menu

    Ball *balls[NUM_BALLS];                          //!< Array of balls in simulation
    Engine::Graphics::RenderableObject *shotAimLine; //!< Line used to show shot acceleration vector

    Engine::Graphics::TextPane *statusLine; //!< Textual status line
    Engine::Graphics::TextPane *foulLine;   //!< Textual status line displaying fouls

    Engine::Common::SceneObject *scoreDisplay;        //!< Parent node of all score related text
    Engine::Graphics::TextPane *player1ScoreText;     //!< Text showing score for player 1
    Engine::Graphics::TextPane *player2ScoreText;     //!< Text showing score for player 2
    Engine::Graphics::TextPane *player1IndicatorText; //!< Turn indicator for player 1
    Engine::Graphics::TextPane *player2IndicatorText; //!< Turn indicator for player 2

  private:
    void initBalls();

  private:
    Uint8 m_graphicsLoop; //!< Graphics update loop ID
    Uint8 m_physicsLoop;  //!< Physics update loop ID
    Uint8 m_controlLoop;  //!< Control update loop ID
    Uint8 m_profileLoop;  //!< Profile update loop ID

    Engine::Common::Scene *m_scene; //!< Scene containing snooker table, etc
    Engine::Common::Scene *m_ui;    //!< Scene containing UI components

    Table *m_table; //!< Snooker table

    TTF_Font *m_fontLarge;                       //!< Large font
    TTF_Font *m_fontMedium;                      //!< Medium font
    Engine::Graphics::ShaderProgram *m_uiShader; //!< Shader program used for UI components
    Engine::Graphics::TextPane *m_profileText;   //!< Profile text display
  };
}
}

#endif
