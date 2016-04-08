/**
 * @file
 * @author Dan Nixon
 */

#include "SnookerStateMachine.h"

#include <Simulation_AI/FunctionalState.h>

#include "SnookerControls.h"
#include "SnookerSimulation.h"

using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  SnookerStateMachine::SnookerStateMachine(SnookerSimulation *simulation)
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
    SnookerSimulation *sim = m_simulation;

    // ROOT STATES

    // Reset state (defaults back to sandbox)
    FunctionalState *reset = new FunctionalState("reset", rootState(), this);
    // Acivate state when reset control is triggered
    reset->setTestTransferTo([sim](const IState *const, StateMachine *sm) -> bool {
      bool change = sim->controls->state(S_RESET);
      if (change)
        sim->controls->setState(S_RESET, false);
      return change;
    });
    // Go to sandbox mode on next update
    reset->setTestTransferFrom(
        [](const IState *const, StateMachine *sm) -> IState * { return sm->rootState()->findState("sandbox").back(); });
    // Perform reset when operated
    reset->setOnOperate([sim](IState *, StateMachine *) {
      sim->physics.setRunning(false);
      sim->placeBalls();
      sim->physics.setRunning(!sim->controls->state(S_PAUSE));
    });

    // Sandbox mode
    FunctionalState *sandbox = new FunctionalState("sandbox", rootState(), this);
    // Go to game mode when the mode is changed
    sandbox->setTestTransferFrom([sim](const IState *const, StateMachine *sm) -> IState * {
      if (sim->controls->state(S_MODE_CHANGE))
      {
        sim->controls->setState(S_MODE_CHANGE, false);
        return sm->rootState()->findState("game").back();
      }
      return nullptr;
    });

    // Game mode
    FunctionalState *game = new FunctionalState("game", rootState(), this);
    // Go to sandbox mode when the mode is changed
    game->setTestTransferFrom([sim](const IState *const, StateMachine *sm) -> IState * {
      if (sim->controls->state(S_MODE_CHANGE))
      {
        sim->controls->setState(S_MODE_CHANGE, false);
        return sm->rootState()->findState("sandbox").back();
      }
      return nullptr;
    });
    // Activate running state then this state is entered
    game->setOnEntry([](IState *s, StateMachine *sm) { s->findState("running").back()->setActivation(true, s); });

    // GAME MODE STATES

    // Game states: idle and game in progress
    new FunctionalState("idle", game, this);
    FunctionalState *running = new FunctionalState("running", game, this);
    // Reset simulation at start of game
    running->setOnOperate([sim](IState *, StateMachine *) {
      sim->physics.setRunning(false);
      sim->placeBalls();
      sim->physics.setRunning(!sim->controls->state(S_PAUSE));
    });

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
