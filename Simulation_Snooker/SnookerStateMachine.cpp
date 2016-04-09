/**
 * @file
 * @author Dan Nixon
 */

#include "SnookerStateMachine.h"

#include <Engine_Graphics/LineMesh.h>
#include <Engine_Maths/Vector2.h>
#include <Engine_Maths/VectorOperations.h>

#include <Simulation_AI/CompletableActionState.h>
#include <Simulation_AI/FunctionalState.h>

#include "SnookerControls.h"
#include "SnookerSimulation.h"
#include "SnookerStates.h"

using namespace Engine::Maths;
using namespace Engine::Graphics;
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
    resetMouseStartPosition();
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
    // Handle controls for taking shots
    sandbox->setOnOperate([this, sim](IState *s, StateMachine *) { this->updateControlTakeShot(nullptr); });

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
    PlayerState *player = new PlayerState(parent, this, playerNumber);

    player->setOnEntry([](IState *s, StateMachine *) {
      // Aim for red in first turn
      // TODO
      dynamic_cast<WaitForShotState *>(s->findState("wait_for_shot").back())->setTargetBallPoints(1);
    });

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
    // Reset recorded mouse start position
    placeCueBall->setOnEntry([this](IState *, StateMachine *) { this->resetMouseStartPosition(); });
    // Handle controls for placing cue ball
    placeCueBall->setOnOperate([this, sim](IState *s, StateMachine *) {
      this->updateControlPlaceCueBall(static_cast<CompletableActionState *>(s));
    });

    // Take shot state
    TakeShotState *takeShot = new TakeShotState(player, this, sim);

    // Wait for shot state
    WaitForShotState *waitForShot = new WaitForShotState(player, this, sim);

    FunctionalState *afterShot = new FunctionalState("after_shot", player, this);

    // AFTER SHOT STATES

    // The shot was foul
    FunctionalState *foulShot = new FunctionalState("foul", afterShot, this);
    // Foul shots gives opponent 4 points
    foulShot->setOnEntry([player](IState *, StateMachine *) { player->otherPlayer()->addToScore(4); });

    FunctionalState *legalShot = new FunctionalState("legal", afterShot, this);

    // FOUL SHOT STATES

    FunctionalState *noBallHit = new FunctionalState("hit_nothing", foulShot, this);
    FunctionalState *hitWrongBall = new FunctionalState("hit_wrong_ball", foulShot, this);
    FunctionalState *potWrongBall = new FunctionalState("pot_wrong_ball", foulShot, this);
    FunctionalState *potCueBall = new FunctionalState("pot_cue_ball", potWrongBall, this);

    // LEGAL SHOT STATES

    FunctionalState *potNothing = new FunctionalState("pot_nothing", legalShot, this);
    FunctionalState *potRed = new FunctionalState("pot_red", legalShot, this);
    FunctionalState *potAnyColour = new FunctionalState("pot_any_colour", legalShot, this);
    FunctionalState *potSequenceColour = new FunctionalState("pot_sequence_colour", legalShot, this);
  }

  /**
  * @brief Update the controls for taking a shot.
  */
  void SnookerStateMachine::updateControlTakeShot(CompletableActionState *state)
  {
    // Mouse clicks (to take shots)
    if (m_mouseStartPosition == nullptr)
    {
      if (m_simulation->controls->state(S_TAKE_SHOT))
      {
        // Record starting position of mouse
        m_mouseStartPosition =
            new Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
        static_cast<LineMesh *>(m_simulation->shotAimLine->mesh())->setTo(Vector3());
        m_simulation->shotAimLine->setActive(true);
      }
      else
      {
        m_simulation->balls[0]->setAcceleration(Vector2());
      }
    }
    else
    {
      Vector2 newMousePosition =
          Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
      Vector2 deltaMouse = *m_mouseStartPosition - newMousePosition;

      // Clamp max acceleration to a sensible level
      float maxShotMagnitude = 0.5f;
      if (deltaMouse.length2() > (maxShotMagnitude * maxShotMagnitude))
        deltaMouse = VectorOperations::GetNormalised(deltaMouse) * maxShotMagnitude;

      if (!m_simulation->controls->state(S_TAKE_SHOT))
      {
        m_simulation->shotAimLine->setActive(false);
        m_simulation->balls[0]->setAcceleration(deltaMouse);
        resetMouseStartPosition();

        if (state != nullptr)
          state->markAsComplete();
      }
      else
      {
        static_cast<LineMesh *>(m_simulation->shotAimLine->mesh())->setTo(deltaMouse * 1000.0f);
      }
    }
  }

  /**
  * @brief Update the controls for placing the cue ball.
  */
  void SnookerStateMachine::updateControlPlaceCueBall(CompletableActionState *state)
  {
    // Mouse clicks (to take shots)
    if (m_mouseStartPosition == nullptr)
    {
      if (m_simulation->controls->state(S_TAKE_SHOT))
      {
        // Record starting position of mouse
        m_mouseStartPosition =
            new Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
      }
    }
    else
    {
      Vector2 newMousePosition =
          Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
      Vector2 deltaMouse = *m_mouseStartPosition - newMousePosition;

      // Clamp max acceleration to a sensible level
      float maxShotMagnitude = 0.5f;
      if (deltaMouse.length2() > (maxShotMagnitude * maxShotMagnitude))
        deltaMouse = VectorOperations::GetNormalised(deltaMouse) * maxShotMagnitude;

      if (!m_simulation->controls->state(S_TAKE_SHOT))
      {
        resetMouseStartPosition();

        if (state != nullptr)
          state->markAsComplete();
      }
      else
      {
        m_simulation->balls[0]->setPosition(newMousePosition * 2000.0f);
      }
    }
  }
}
}
