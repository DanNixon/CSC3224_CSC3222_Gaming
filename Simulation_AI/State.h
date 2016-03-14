/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_STATE_H_
#define _SIMULATION_AI_STATE_H_

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
  class State
  {
  public:
    State(State *parent);
    virtual ~State();

    /**
     * @brief Perform the operations that define the behaviour of this state.
     */
    virtual void operate() = 0;

    /**
     * @brief Test for transfer conditions to another state.
     * @return The state to transfer to, NULL if no transfer conditions are met
     */
    virtual State *transferCheck() const = 0;

  protected:
    State *m_parent;                 //!< Parent state
    std::vector<State *> m_children; //!< Child states
  };
}
}

#endif
