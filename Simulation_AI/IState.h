/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
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

  /**
   * @typedef IStatePtrList
   * @brief List of pointers to IState instances.
   */
  typedef std::vector<IState *> IStatePtrList;

  /**
   * @typedef IStatePtrListIter
   * @brief Iterator over a list of pointers to IState instances.
   */
  typedef IStatePtrList::iterator IStatePtrListIter;

  /**
   * @typedef IStatePtrListConstIter
   * @brief Iterator over a const list of pointers to IState instances.
   */
  typedef IStatePtrList::const_iterator IStatePtrListConstIter;

  /**
   * @class IState
   * @brief Represents a state in a state machine.
   * @author Dan Nixon
   */
  class IState : public StateContainer
  {
  public:
    static IState *ClosestCommonAncestor(IState *a, IState *b);

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
     * @brief Returns the parent state of this state.
     * @return Parent state
     */
    inline IState *parent() const
    {
      return m_parent;
    }

    /**
     * @brief Checks if this IState is active.
     * @return True if this IState is active
     */
    inline bool isActive() const
    {
      return m_parent->activeChild() == this;
    }

    IStatePtrList branch(bool reverse = false);

    void setActivation(bool active, IState *terminateAt = nullptr, IState *delta = nullptr);

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
     * @brief Test for transfer conditions from this state to another.
     * @return The IState to transfer to, nullptr if no transfer conditions are
     *         met
     */
    virtual IState *testTransferFrom() const
    {
      return nullptr;
    }

    /**
    * @brief Test for transfer conditions from a sibling state to this state.
    * @return True if the transfer conditions are met.
    */
    virtual bool testTransferTo() const
    {
      return false;
    }

    /**
     * @brief Performs actions required when entering this state.
     * @param last Last state to be active
     */
    virtual void onEntry(IState *last)
    {
    }

    /**
     * @brief Performs actions required when leaving this state.
     * @param next State that is going to be entered next
     */
    virtual void onExit(IState *next)
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
