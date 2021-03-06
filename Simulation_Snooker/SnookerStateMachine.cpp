/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#include "SnookerStateMachine.h"

#include <Engine_Graphics/LineMesh.h>
#include <Engine_Maths/Vector2.h>
#include <Engine_Maths/VectorOperations.h>

#include <Simulation_AI/CompletableActionState.h>
#include <Simulation_AI/FunctionalState.h>

#include "SandboxState.h"
#include "SnookerControls.h"
#include "SnookerSimulation.h"

using namespace Engine::Maths;
using namespace Engine::Graphics;
using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  /**
   * @copydoc StateMachine::StateMachine
   * @param simulation Simulation acted upon
   */
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
      sim->resetBalls();
      sim->physics.setRunning(!sim->controls->state(S_PAUSE));
    });

    // Sandbox mode
    IState *sandbox = new SandboxState(rootState(), this, m_simulation);

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
      sim->scoreDisplay->setActive(true);
      // Activate running state then this state is entered
      s->findState("running").back()->setActivation(true, s);
    });
    game->setOnExit([sim](IState *s, StateMachine *sm, IState *) {
      // Hide the score display when leaving game mode
      sim->scoreDisplay->setActive(false);
      sim->foulLine->setActive(false);
    });

    // GAME MODE STATES

    // Idle game state
    FunctionalState *idle = new FunctionalState("idle", game, this);
    idle->setOnEntry([sim](IState *, StateMachine *, IState *) { sim->statusLine->setText("Game Over"); });

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
    foulShot->setOnEntry([sim, player](IState *, StateMachine *, IState *) {
      // Foul shots gives opponent 4 points
      player->otherPlayer()->addToScore(4);
      // Show the fould status line
      sim->foulLine->setActive(true);
    });
    foulShot->setTestTransferFrom(nextPlayersTurn);

    FunctionalState *legalShot = new FunctionalState("legal", afterShot, this);

    // FOUL SHOT STATES

    FunctionalState *noBallHit = new FunctionalState("hit_nothing", foulShot, this);
    noBallHit->setOnEntry([sim](IState *, StateMachine *, IState *) { sim->foulLine->setText("Foul: no ball hit"); });

    FunctionalState *hitWrongBall = new FunctionalState("hit_wrong_ball", foulShot, this);
    hitWrongBall->setOnEntry(
        [sim](IState *, StateMachine *, IState *) { sim->foulLine->setText("Foul: incorrect ball hit"); });

    FunctionalState *potWrongBall = new FunctionalState("pot_wrong_ball", foulShot, this);
    potWrongBall->setOnEntry(
        [sim](IState *, StateMachine *, IState *) { sim->foulLine->setText("Foul: incorrect ball potted"); });
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
    potCueBall->setOnEntry(
        [sim](IState *, StateMachine *, IState *) { sim->foulLine->setText("Foul: cue ball potted"); });

    // LEGAL SHOT STATES

    auto playerTakesNextShot = [player](const IState *const, StateMachine *sm) {
      return player->findState("take_shot").back();
    };

    FunctionalState *potNothing = new FunctionalState("pot_nothing", legalShot, this);
    potNothing->setTestTransferFrom(nextPlayersTurn);

    FunctionalState *potRed = new FunctionalState("pot_red", legalShot, this);
    potRed->setTestTransferFrom(playerTakesNextShot);
    // One point for potting a red
    potRed->setOnEntry([player](IState *, StateMachine *, IState *) { player->addToScore(1); });

    // Some points for potting a colour
    auto pointsForColour = [player, waitForShot](IState *, StateMachine *, IState *) {
      Ball *b = waitForShot->lastPotted();
      if (b != nullptr)
        player->addToScore(b->points());
    };

    FunctionalState *potAnyColour = new FunctionalState("pot_any_colour", legalShot, this);
    potAnyColour->setTestTransferFrom(playerTakesNextShot);
    potAnyColour->setOnEntry(pointsForColour);

    FunctionalState *potSequenceColour = new FunctionalState("pot_sequence_colour", legalShot, this);
    potSequenceColour->setOnEntry(pointsForColour);
    potSequenceColour->setTestTransferFrom([sim, player](const IState *const, StateMachine *sm) -> IState * {
      for (size_t i = 1; i < SnookerSimulation::NUM_BALLS; i++)
      {
        if (sim->balls[i] != nullptr && sim->balls[i]->collides())
          return player->otherPlayer();
      }

      return sm->rootState()->findState("game/idle").back();
    });
  }
}
}
