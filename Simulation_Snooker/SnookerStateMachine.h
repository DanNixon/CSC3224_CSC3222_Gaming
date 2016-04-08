/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_SNOOKERSTATEMACHINE_H_
#define _SIMULATION_SNOOKER_SNOOKERSTATEMACHINE_H_

#include <Simulation_AI/StateMachine.h>

namespace Simulation
{
namespace Snooker
{
  /**
   * @class SnookerStateMachine
   * @brief State machine for running a game of snooker on the simulator.
   * @author Dan Nixon
   */
  class SnookerStateMachine : public Simulation::AI::StateMachine
  {
  public:
    SnookerStateMachine();
    virtual ~SnookerStateMachine();

    void initStates();

  private:
    void addPlayerStates(Simulation::AI::IState *parent, int playerNumber);
  };
}
}

#endif
