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
  /**
   * @class WaitForShotState
   * @brief State used to observe the simulation after a shot has been taken to
   *        record first ball touched and balls potted.
   * @author Dan Nixon
   */
  class WaitForShotState : public Simulation::AI::IState
  {
  public:
    WaitForShotState::WaitForShotState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine,
                                       SnookerSimulation *simulation, const std::string &name = "wait_for_shot");

    /**
     * @brief Sets the number of points the target ball is worth.
     * @param points Points, 0 for any colour
     *
     * This is used to determine if the shot was valid.
     */
    inline void setTargetBallPoints(int points)
    {
      m_targetBallPoints = points;
    }

    /**
     * @brief Gets the number of points the target ball is worth.
     * @return Points, 0 for any colour ball
     */
    inline int targetBallPoints() const
    {
      return m_targetBallPoints;
    }

    /**
     * @brief Gets a pointer to the last ball that was potted.
     * @return Last ball potted, nullptr if no balls were potted
     */
    inline Ball *lastPotted()
    {
      if (m_potted.empty())
        return nullptr;
      else
        return m_potted.back();
    }

    /**
     * @brief Gets a reference to a vector containing pointers to balls that
     *        have been potted.
     * @return Balls potted
     *
     * Vector is sorted by the order that the balls were potted.
     */
    inline std::vector<Ball *> &potted()
    {
      return m_potted;
    }

  protected:
    virtual Simulation::AI::IState *testTransferFrom() const;
    virtual void onEntry(Simulation::AI::IState *last);
    virtual void onOperate();

  protected:
    SnookerSimulation *m_simulation; //!< Simulaion state is acting on
    int m_targetBallPoints;          //!< Points the target ball is worth (0 for any colour)
    Ball *m_firstCueBallTouched;     //!< Pointer to the first ball touched by the cue ball
    std::vector<Ball *> m_potted;    //!< Balls potted (in order of having been potted)
  };
}
}

#endif
