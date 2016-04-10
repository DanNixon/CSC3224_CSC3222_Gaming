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
    WaitForShotState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine,
                     SnookerSimulation *simulation)
        : IState("wait_for_shot", parent, machine)
        , m_simulation(simulation)
        , m_targetBallPoints(-1)
    {
    }

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
    virtual IState *testTransferFrom() const
    {
      if (m_simulation->physics.atRest())
      {
        // Cue ball was potted
        if (std::find(m_potted.begin(), m_potted.end(), m_simulation->balls[0]) != m_potted.end())
          return m_parent->findState("after_shot/foul/pot_wrong_ball/pot_cue_ball").back();

        // No ball was touched
        if (m_firstCueBallTouched == nullptr)
          return m_parent->findState("after_shot/foul/hit_nothing").back();

        // A specific correct ball was potted
        if (m_potted.size() == 1 && m_potted[0]->points() == m_targetBallPoints)
        {
          if (m_targetBallPoints == 1)
            return m_parent->findState("after_shot/legal/pot_red").back();
          else
            return m_parent->findState("after_shot/legal/pot_sequence_colour").back();
        }

        // Any colour was potted
        if (m_potted.size() == 1 && m_potted[0]->points() > 1 && m_targetBallPoints == 0)
          return m_parent->findState("after_shot/legal/pot_any_colour").back();

        // Wrong ball was potted
        if (!m_potted.empty())
          return m_parent->findState("after_shot/foul/pot_wrong_ball").back();

        // Hit incorrect ball
        if (m_targetBallPoints != m_firstCueBallTouched->points() ||
            (m_targetBallPoints == 0 && m_firstCueBallTouched->points() == 1))
          return m_parent->findState("after_shot/foul/hit_wrong_ball").back();

        // Did not pot anything
        if (m_potted.empty())
          return m_parent->findState("after_shot/legal/pot_nothing").back();

        return nullptr;
      }

      return nullptr;
    }

    virtual void onEntry(IState *last)
    {
      (void)last;
      m_firstCueBallTouched = nullptr;
      m_potted.clear();
    }

    virtual void onOperate()
    {
      std::vector<Simulation::Physics::InterfaceDef> inters = m_simulation->physics.interfaces();
      Ball *cueBall = m_simulation->balls[0];

      for (auto it = inters.begin(); it != inters.end(); ++it)
      {
        // Record the first ball the cue ball touches
        if (m_firstCueBallTouched == nullptr && it->contains(cueBall))
          m_firstCueBallTouched = dynamic_cast<Ball *>(it->otherNot(cueBall));

        // Record potted balls
        Simulation::Physics::Entity *a = it->entityA();
        Simulation::Physics::Entity *b = it->entityB();

        Ball *potted = nullptr;
        if (dynamic_cast<Pocket *>(a))
          potted = dynamic_cast<Ball *>(b);
        else if (dynamic_cast<Pocket *>(b))
          potted = dynamic_cast<Ball *>(a);

        if (potted && (std::find(m_potted.begin(), m_potted.end(), potted) == m_potted.end()))
        {
          // Record his ball as being potted
          m_potted.push_back(potted);

          // Reset to default position and stop motion
          potted->reset(true);

          // Set no collide
          potted->setCollide(false);

          // Make invisivle
          potted->setActive(false);
        }
      }
    }

  private:
    SnookerSimulation *m_simulation;
    Ball *m_firstCueBallTouched;
    std::vector<Ball *> m_potted;
    int m_targetBallPoints;
  };
}
}

#endif