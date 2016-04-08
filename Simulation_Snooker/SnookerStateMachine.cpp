/**
 * @file
 * @author Dan Nixon
 */

#include "SnookerStateMachine.h"

#include "SnookerControls.h"
#include "SnookerSimulation.h"
#include "SnookerStates.h"

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

    // Idle game state
    new FunctionalState("idle", game, this);

    // Running game state
    FunctionalState *running = new FunctionalState("running", game, this);
    // At start of game
    running->setOnEntry([sim](IState *s, StateMachine *sm) {
      // Reset the simulation
      sim->physics.setRunning(false);
      sim->placeBalls();
      sim->physics.setRunning(!sim->controls->state(S_PAUSE));
      // Player 0 to pace the cue ball
      sm->rootState()->findState("game/running/player_0/place_cue_ball").back()->setActivation(true, s);
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
    SnookerSimulation *sim = m_simulation;
    FunctionalState *player = new PlayerState(parent, this, playerNumber);

    // FOUR GENERAL PLAY STATES: place cue ball, take shot, wait for shot, after shot

    // Place cue ball state
    FunctionalState *placeCueBall = new CompletableActionState("place_cue_ball", player, this);
    // Move to take shot when ball is placed
    placeCueBall->setTestTransferFrom([](const IState *const s, StateMachine *sm) -> IState * {
      if (static_cast<const CompletableActionState *>(s)->completed())
        return s->parent()->findState("take_shot").back();
      else
        return nullptr;
    });

    // Take shot state
    FunctionalState *takeShot = new CompletableActionState("take_shot", player, this);
    // Move to wait for shot when shot is taken
    takeShot->setTestTransferFrom([](const IState *const s, StateMachine *sm) -> IState * {
      if (static_cast<const CompletableActionState *>(s)->completed())
        return s->parent()->findState("wait_for_shot").back();
      else
        return nullptr;
    });

    // Wait for shot state
    FunctionalState *waitForShot = new FunctionalState("wait_for_shot", player, this);
    // Transfer to after shot when simulation is at rest
    waitForShot->setTestTransferFrom([sim](const IState *const s, StateMachine *sm) -> IState * {
      if (sim->physics.atRest())
        return s->parent()->findState("after_shot").back();
      else
        return nullptr;
    });

    FunctionalState *afterShot = new FunctionalState("after_shot", player, this);

    // AFTER SHOT STATES

    FunctionalState *foulShot = new FunctionalState("foul", afterShot, this);
    FunctionalState *legalShot = new FunctionalState("legal", afterShot, this);

    // FOUL SHOT STATES

    FunctionalState *noBallHit = new FunctionalState("no_ball_hit", foulShot, this);
    FunctionalState *hitWrongBall = new FunctionalState("hit_wrong_ball", foulShot, this);
    FunctionalState *potWrongBall = new FunctionalState("pot_wrong_ball", foulShot, this);
    FunctionalState *potCueBall = new FunctionalState("pot_cue_ball", foulShot, this);

    // VALID SHOT STATES

    FunctionalState *potRed = new FunctionalState("pot_red", legalShot, this);
    FunctionalState *potAnyColour = new FunctionalState("pot_any_colour", legalShot, this);
    FunctionalState *potSequenceColour = new FunctionalState("pot_sequence_colour", legalShot, this);
  }
}
}
