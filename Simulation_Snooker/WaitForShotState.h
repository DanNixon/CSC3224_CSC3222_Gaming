/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_WAITFORSHOTSTATE_H_
#define _SIMULATION_SNOOKER_WAITFORSHOTSTATE_H_

#include <string>

#include <Simulation_AI/IState.h>
#include <Simulation_AI/StateMachine.h>

#include "SnookerSimulation.h"

namespace Simulation
{
namespace Snooker
{
  class WaitForShotState : public Simulation::AI::IState
  {
  public:
    WaitForShotState::WaitForShotState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine,
                                       SnookerSimulation *simulation);

    inline void setTargetBallPoints(int points)
    {
      m_targetBallPoints = points;
    }

    inline int targetBallPoints() const
    {
      return m_targetBallPoints;
    }

    inline Ball *lastPotted()
    {
      if (m_potted.empty())
        return nullptr;
      else
        return m_potted.back();
    }

    inline std::vector<Ball *> &potted()
    {
      return m_potted;
    }

  protected:
    virtual Simulation::AI::IState *testTransferFrom() const;
    virtual void onEntry(Simulation::AI::IState *last);
    virtual void onOperate();

  private:
    SnookerSimulation *m_simulation;
    Ball *m_firstCueBallTouched;
    std::vector<Ball *> m_potted;
    int m_targetBallPoints;
  };
}
}

#endif