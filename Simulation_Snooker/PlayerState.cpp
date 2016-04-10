/**
 * @file
 * @author Dan Nixon
 */

#include "PlayerState.h"

using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  PlayerState::PlayerState(IState *parent, StateMachine *machine, int playerNumber, SnookerSimulation *simulation)
      : FunctionalState("player_" + std::to_string(playerNumber), parent, machine)
      , m_playerNumber(playerNumber)
      , m_score(0)
      , m_simulation(simulation)
  {
  }

  void PlayerState::updateScoreText() const
  {
    if (m_playerNumber == 0)
      m_simulation->player1ScoreText->setText(std::to_string(m_score));
    else if (m_playerNumber == 1)
      m_simulation->player2ScoreText->setText(std::to_string(m_score));
  }

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

  PlayerState *PlayerState::otherPlayer()
  {
    if (m_otherPlayer == nullptr)
    {
      std::string name = "game/running/player_" + std::to_string((m_playerNumber + 1) % 2);
      m_otherPlayer = dynamic_cast<PlayerState *>(m_machine->rootState()->findState(name).back());
    }

    return m_otherPlayer;
  }
}
}