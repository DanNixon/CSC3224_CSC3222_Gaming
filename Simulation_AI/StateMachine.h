/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_STATEMACHINE_H_
#define _SIMULATION_AI_STATEMACHINE_H_

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
  class StateMachine
  {
  public:
    StateMachine();
    virtual ~StateMachine();

  private:
    std::vector<State *> m_states; //!< All first level states
  };
}
}

#endif
