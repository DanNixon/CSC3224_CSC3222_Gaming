/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_STATES_H_
#define _SIMULATION_SNOOKER_STATES_H_

#include <string>

#include <Simulation_AI/FunctionalState.h>
#include <Simulation_AI/IState.h>
#include <Simulation_AI/StateMachine.h>

namespace Simulation
{
namespace Snooker
{
  class PlayerState : public Simulation::AI::FunctionalState
  {
  public:
    PlayerState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine, int playerNumber)
        : FunctionalState("player_" + std::to_string(playerNumber), parent, machine)
        , m_playerNumber(playerNumber)
        , m_score(0)
    {
    }

    inline int playerNumber() const
    {
      return m_playerNumber;
    }

    inline int score() const
    {
      return m_score;
    }

    inline void addToScore(int points)
    {
      m_score += points;
    }

    IState *otherPlayer() const
    {
      std::string name = "game/running/player_" + std::to_string((m_playerNumber + 1) % 2);
      return m_machine->rootState()->findState(name).back();
    }

  private:
    int m_playerNumber; //!< Player number (0 or 1)
    int m_score;        //!< Players score
  };

  class CompletableActionState : public Simulation::AI::FunctionalState
  {
  public:
    CompletableActionState(const std::string &name, Simulation::AI::IState *parent,
                           Simulation::AI::StateMachine *machine)
        : FunctionalState(name, parent, machine)
        , m_completed(false)
    {
    }

    bool completed() const
    {
      return m_completed;
    }

    void markAsComplete()
    {
      m_completed = true;
    }

  private:
    bool m_completed; //!< Flag indicating completion
  };
}
}

#endif
