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
      sim->resetBalls();
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
    game->setOnEntry([sim](IState *s, StateMachine *sm, IState *) {
      // Show the score display
      sim->scoreDisplay->setActive(true, 10);
      // Activate running state then this state is entered
      s->findState("running").back()->setActivation(true, s);
    });
    game->setOnExit([sim](IState *s, StateMachine *sm, IState *) {
      // Hide the score display when leaving game mode
      sim->scoreDisplay->setActive(false, 10);
    });

    // GAME MODE STATES

    // Idle game state
    new FunctionalState("idle", game, this);

    // Running game state
    FunctionalState *running = new FunctionalState("running", game, this);
    // At start of game
    running->setOnEntry([running, sim](IState *s, StateMachine *sm, IState *) {
      // Reset the simulation
      sim->physics.setRunning(false);
      sim->resetBalls();
      sim->physics.setRunning(!sim->controls->state(S_PAUSE));
      // Reset scoring
      static_cast<PlayerState *>(s->findState("player_0").back())->reset();
      static_cast<PlayerState *>(s->findState("player_1").back())->reset();
      // Player 0 to go first
      sm->rootState()->findState("game/running/player_0").back()->setActivation(true, s, running);
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

    PlayerState *player = new PlayerState(parent, this, playerNumber, m_simulation);

    // FOUR GENERAL PLAY STATES: place cue ball, take shot, wait for shot, after shot

    // Place cue ball state
    IState *placeCueBall = new PlaceCueBallState(player, this, sim);

    // Take shot state
    TakeShotState *takeShot = new TakeShotState(player, this, sim);

    // Wait for shot state
    WaitForShotState *waitForShot = new WaitForShotState(player, this, sim);

    FunctionalState *afterShot = new FunctionalState("after_shot", player, this);

    auto nextPlayersTurn = [player](const IState *const, StateMachine *) { return player->otherPlayer(); };

    // AFTER SHOT STATES

    // The shot was foul
    FunctionalState *foulShot = new FunctionalState("foul", afterShot, this);
    // Foul shots gives opponent 4 points
    foulShot->setOnEntry([player](IState *, StateMachine *, IState *) { player->otherPlayer()->addToScore(4); });
    foulShot->setTestTransferFrom(nextPlayersTurn);

    FunctionalState *legalShot = new FunctionalState("legal", afterShot, this);

    // FOUL SHOT STATES

    FunctionalState *noBallHit = new FunctionalState("hit_nothing", foulShot, this);
    FunctionalState *hitWrongBall = new FunctionalState("hit_wrong_ball", foulShot, this);

    FunctionalState *potWrongBall = new FunctionalState("pot_wrong_ball", foulShot, this);
    // Reset incorrectly potted balls
    potWrongBall->setOnOperate([waitForShot, sim](IState *, StateMachine *) {
      int targetPoints = waitForShot->targetBallPoints();
      for (auto it = waitForShot->potted().begin(); it != waitForShot->potted().end(); ++it)
      {
        int ballPoints = (*it)->points();
        if (ballPoints == -1 || (targetPoints == 0 && ballPoints == 1) || (targetPoints != ballPoints))
          sim->resetBalls(static_cast<SnookerBalls>(ballPoints));
      }
    });

    FunctionalState *potCueBall = new FunctionalState("pot_cue_ball", potWrongBall, this);

    // LEGAL SHOT STATES

    auto playerTakesNextShot = [player](const IState *const, StateMachine *sm) {
      return player->findState("take_shot").back();
    };

    FunctionalState *potNothing = new FunctionalState("pot_nothing", legalShot, this);
    potNothing->setTestTransferFrom(nextPlayersTurn);

    FunctionalState *potRed = new FunctionalState("pot_red", legalShot, this);
    potRed->setTestTransferFrom(playerTakesNextShot);

    FunctionalState *potAnyColour = new FunctionalState("pot_any_colour", legalShot, this);
    potAnyColour->setTestTransferFrom(playerTakesNextShot);

    FunctionalState *potSequenceColour = new FunctionalState("pot_sequence_colour", legalShot, this);
    potSequenceColour->setTestTransferFrom([sim, player](const IState *const, StateMachine *sm) -> IState * {
      for (size_t i = 1; i < SnookerSimulation::NUM_BALLS; i++)
      {
        if (sim->balls[i]->collides())
          return player->otherPlayer();
      }

      return sm->rootState()->findState("game/idle").back();
    });
  }

  /**
   * @brief Update the controls for taking a shot.
   */
  void SnookerStateMachine::updateControlTakeShot(CompletableActionState *state)
  {
    if (m_simulation->menu->isMouseOver())
      return;

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
}
}
