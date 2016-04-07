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
  class StateMachine
  {
  public:
    StateMachine();
    virtual ~StateMachine();

    std::vector<State *> activeStateBranch();

    /**
     * @brief Gets the root state for the state machine.
     * @return Root state
     */
    State *rootState()
    {
      return &m_root;
    }

    /**
     * @brief Performs updates of the state machine by checking for transition
     *        conditions then performing operations over all active states.
     * @see StateMachine:transfer()
     * @see StateMachine:operate()
     */
    inline void update()
    {
      transfer();
      operate();
    }

    void transfer();
    void operate();

  private:
    State m_root; //!< Root state
  };
}
}

#endif
