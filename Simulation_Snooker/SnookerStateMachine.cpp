/**
 * @file
 * @author Dan Nixon
 */

#include "SnookerStateMachine.h"

#include <Simulation_AI/FunctionalState.h>

#include "SnookerSimulation.h"

using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  SnookerStateMachine::SnookerStateMachine(SnookerSimulation * simulation)
    : m_simulation(simulation)
  {
  }

  SnookerStateMachine::~SnookerStateMachine()
  {
  }

  /**
   * @brief Populates state tree.
   */
  void SnookerStateMachine::initStates()
  {
    SnookerSimulation * sim = m_simulation;

    // Root modes: game and sandbox
    FunctionalState *sandbox = new FunctionalState("sandbox", rootState(), this);
    sandbox->setOnEntry([sim](IState *, StateMachine *){
      sim->physics.setRunning(false);
      sim->placeBalls();
      sim->physics.setRunning(true);
    });

    // Reset state (defaults back to sandbox)
    FunctionalState *reset = new FunctionalState("reset", rootState(), this);
    reset->setTestTransferCase([](const IState * const, StateMachine *sm) -> IState * {
      return sm->rootState()->findState("sandbox").back();
    });

    FunctionalState *game = new FunctionalState("game", rootState(), this);

    // Game states: idle and game in progress
    new FunctionalState("idle", game, this);
    FunctionalState *running = new FunctionalState("running", game, this);

    // Identical state trees for each player
    addPlayerStates(running, 0);
    addPlayerStates(running, 1);

    // Set default state
    rootState()->findState("sandbox").back()->setActivation(true);
  }

  /**
   * @brief Populates state tree for each player.
   * @param parent Parent tree node
   * @param playerNumber Either 0 or 1
   */
  void SnookerStateMachine::addPlayerStates(IState *parent, int playerNumber)
  {
    IState *player = new FunctionalState("player_" + std::to_string(playerNumber), parent, this);

    // Four general play states: place cue ball, take shot, wait for shot, after shot
    IState *placeCueBall = new FunctionalState("place_cue_ball", player, this);
    IState *takeShot = new FunctionalState("take_shot", player, this);
    IState *waitForShot = new FunctionalState("wait_for_shot", player, this);
    IState *afterShot = new FunctionalState("after_shot", player, this);

    // After a shot was taken it is either a foul or legal
    IState *foulShot = new FunctionalState("foul", afterShot, this);
    IState *legalShot = new FunctionalState("legal", afterShot, this);

    // States for a foul shot
    IState *noBallHit = new FunctionalState("no_ball_hit", foulShot, this);
    IState *hitWrongBall = new FunctionalState("hit_wrong_ball", foulShot, this);
    IState *potWrongBall = new FunctionalState("pot_wrong_ball", foulShot, this);
    IState *potCueBall = new FunctionalState("pot_cue_ball", foulShot, this);

    // States for a valid shot
    IState *potRed = new FunctionalState("pot_red", legalShot, this);
    IState *potColour = new FunctionalState("pot_colour", legalShot, this);
    IState *potBlack = new FunctionalState("pot_black", legalShot, this);
  }
}
}
