/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_STATEMACHINE_H_
#define _SIMULATION_AI_STATEMACHINE_H_

#include "StateContainer.h"

#include <vector>

#include "State.h"

namespace Simulation
{
namespace AI
{
  /**
   * @class StateMachine
   * @brief Represents a state machine
   * @author Dan Nixon
   */
  class StateMachine : public StateContainer
  {
  public:
    StateMachine();
    virtual ~StateMachine();

    std::vector<State *> activeStateBranch();

    inline void update()
    {
      transfer();
      operate();
    }

    void transfer();
    void operate();
  };
}
}

#endif
