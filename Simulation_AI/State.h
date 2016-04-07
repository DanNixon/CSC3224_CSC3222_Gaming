/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_STATE_H_
#define _SIMULATION_AI_STATE_H_

#include "StateContainer.h"

#include <vector>

namespace Simulation
{
namespace AI
{
  /**
   * @class State
   * @brief Represents a state in a StateMachine.
   * @author Dan Nixon
   */
  class State : public StateContainer
  {
  public:
    State(State *parent);
    virtual ~State();

    /**
     * @brief Checks if this state is active.
     * @return True if this state is active
     */
    inline bool isActive() const
    {
      return m_parent->m_active == this;
    }

    /**
     * @brief Test for transfer conditions to another state.
     * @return The state to transfer to, nullptr if no transfer conditions are met
     */
    virtual State *testTransferCase() const = 0;

    /**
     * @brief Performs actions required when entering this state.
     */
    virtual void onEntry()
    {
    }

    /**
     * @brief Performs actions required when leaving this state.
     */
    virtual void onExit()
    {
    }

    /**
     * @brief Perform the operations that define the behaviour of this state.
     */
    virtual void onOperate()
    {
    }

  protected:
    State *m_parent; //!< Parent state
  };
}
}

#endif
