/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_ISTATE_H_
#define _SIMULATION_AI_ISTATE_H_

#include "StateContainer.h"

#include <iostream>
#include <string>
#include <vector>

namespace Simulation
{
namespace AI
{
  class StateMachine;

  typedef std::vector<IState *> IStatePtrList;
  typedef IStatePtrList::iterator IStatePtrListIter;
  typedef IStatePtrList::const_iterator IStatePtrListConstIter;

  /**
   * @class IState
   * @brief Represents a state in a state machine.
   * @author Dan Nixon
   */
  class IState : public StateContainer
  {
  public:
    IState(const std::string &name, IState *parent, StateMachine *machine);
    virtual ~IState();

    /**
     * @brief Gets the name of this IState.
     * @return IState name
     */
    inline std::string name() const
    {
      return m_name;
    }

    /**
     * @brief Checks if this IState is active.
     * @return True if this IState is active
     */
    inline bool isActive() const
    {
      return m_parent->activeChild() == this;
    }

    IStatePtrList branch();

    void setActivation(bool active);

    /**
     * @brief Outputs a state to a stream.
     * @param o Stream to output to
     * @param s IState to output
     * @return Stream
     */
    inline friend std::ostream &operator<<(std::ostream &o, const IState &s)
    {
      o << "IState(" << std::string(s.m_name) << ")";
      return o;
    }

  protected:
    friend class StateMachine;

    /**
     * @brief Test for transfer conditions to another IState.
     * @return The IState to transfer to, nullptr if no transfer conditions are
     *         met
     */
    virtual IState *testTransferCase() const
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
    IState *m_parent;         //!< Parent state
  };
}
}

#endif
