/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_STATE_H_
#define _SIMULATION_AI_STATE_H_

#include "StateContainer.h"

#include <iostream>
#include <string>
#include <vector>

namespace Simulation
{
namespace AI
{
  class StateMachine;

  /**
   * @class State
   * @brief Represents a state in a StateMachine.
   * @author Dan Nixon
   */
  class State : public StateContainer
  {
  public:
    State(const std::string &name, State *parent);
    virtual ~State();

    /**
     * @brief Gets the name of this state.
     * @return State name
     */
    inline std::string name() const
    {
      return m_name;
    }

    /**
     * @brief Checks if this state is active.
     * @return True if this state is active
     */
    inline bool isActive() const
    {
      return m_parent->activeChild() == this;
    }

    std::vector<State *> branch();

    void setActivation(bool active);

    /**
     * @brief Outputs a state to a stream.
     * @param o Stream to output to
     * @param s State to output
     * @return Stream
     */
    inline friend std::ostream &operator<<(std::ostream &o, const State &s)
    {
      o << "State(" << std::string(s.m_name) << ")";
      return o;
    }

  protected:
    friend class StateMachine;

    /**
     * @brief Test for transfer conditions to another state.
     * @return The state to transfer to, nullptr if no transfer conditions are
     *         met
     */
    virtual State *testTransferCase() const
    {
      return nullptr;
    }

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
    const std::string m_name; //!< Name of this state
    StateMachine *m_machine;  //!< State machine that holds this state
    State *m_parent;          //!< Parent state
  };
}
}

#endif
