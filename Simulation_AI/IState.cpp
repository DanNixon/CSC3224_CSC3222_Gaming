/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#include "IState.h"

namespace Simulation
{
namespace AI
{
  /**
   * @brief Finds the closest common ancestor of two states.
   * @param a First state
   * @param b Second state
   * @return Closest ancestor, nullptr if no common ancestor
   */
  IState *IState::ClosestCommonAncestor(IState *a, IState *b)
  {
    IStatePtrList branchA = a->branch();
    IStatePtrList branchB = b->branch();

    IStatePtrListIter ia = branchA.begin();
    IStatePtrListIter ib = branchB.begin();

    IState *commonAncestor = nullptr;

    // Taverse down common sections of each branch until the branches diverge
    while (*ia == *ib)
    {
      commonAncestor = *ia;

      ++ia;
      ++ib;

      // Exit when either branch terminates (i.e. either state is an ancestor of the other)
      if (ia == branchA.end() || ib == branchB.end())
        break;
    }

    return commonAncestor;
  }

  /**
   * @brief Create a new state.
   * @param name Name of this state
   * @param parent Parent state
   * @param machine The state machine to which this state belongs
   */
  IState::IState(const std::string &name, IState *parent, StateMachine *machine)
      : m_name(name)
      , m_machine(machine)
      , m_parent(parent)
  {
    if (parent)
      parent->m_children.push_back(this);
  }

  IState::~IState()
  {
  }

  /**
   * @brief Gets the branch of the state tree that leads to this node.
   * @param reverse If the branch order should be reversed
   * @return State tree branch
   */
  IStatePtrList IState::branch(bool reverse)
  {
    IStatePtrList branch;

    IState *node = this;
    while (node != nullptr)
    {
      branch.push_back(dynamic_cast<IState *>(node));
      node = node->m_parent;
    }

    if (!reverse)
      std::reverse(branch.begin(), branch.end());

    return branch;
  }

  /**
   * @brief Sets the activation of this state and its ancestors.
   * @param active If this state is active or not
   * @param terminateAt Ancestor at which to stop modifying activation
   */
  void IState::setActivation(bool active, IState *terminateAt, IState *delta)
  {
    if (terminateAt == this)
      return;

    if (!active)
      onExit(delta);

    if (m_parent)
    {
      m_parent->m_active = active ? this : nullptr;
      m_parent->setActivation(active, terminateAt);
    }

    if (active)
      onEntry(delta);
  }
}
}
