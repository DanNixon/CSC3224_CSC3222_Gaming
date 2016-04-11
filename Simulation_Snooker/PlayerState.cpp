/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#include "PlayerState.h"

using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  /**
   * @brief Creates a new player state
   * @param parent Parent state
   * @param machine State machine
   * @param playerNumber Player number (either 0 or 1)
   * @param simulation Snooker simulation
   */
  PlayerState::PlayerState(IState *parent, StateMachine *machine, int playerNumber, SnookerSimulation *simulation)
      : FunctionalState("player_" + std::to_string(playerNumber), parent, machine)
      , m_playerNumber(playerNumber)
      , m_score(0)
      , m_simulation(simulation)
  {
  }

  /**
   * @brief Updates the score display on the simulation with this players
   *        score.
   */
  void PlayerState::updateScoreText() const
  {
    if (m_playerNumber == 0)
      m_simulation->player1ScoreText->setText(std::to_string(m_score));
    else if (m_playerNumber == 1)
      m_simulation->player2ScoreText->setText(std::to_string(m_score));
  }

  /**
   * @brief Gets a pointer to the other player in the game branch.
   * @return Pointer to other player
   */
  PlayerState *PlayerState::otherPlayer()
  {
    if (m_otherPlayer == nullptr)
    {
      std::string name = "game/running/player_" + std::to_string((m_playerNumber + 1) % 2);
      m_otherPlayer = dynamic_cast<PlayerState *>(m_machine->rootState()->findState(name).back());
    }

    return m_otherPlayer;
  }

  /**
   * @copydoc FunctionalState::onEntry
   */
  void PlayerState::onEntry(IState *last)
  {
    updateScoreText();

    // Update current player indicator
    m_simulation->player1IndicatorText->setActive(m_playerNumber == 0);
    m_simulation->player2IndicatorText->setActive(m_playerNumber == 1);

    if (last->name() == "pot_cue_ball" || last->name() == "running")
      findState("place_cue_ball").back()->setActivation(true, this, this);
    else
      findState("take_shot").back()->setActivation(true, this, this);
  }
}
}
