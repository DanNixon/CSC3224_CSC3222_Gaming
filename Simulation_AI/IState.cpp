/**
 * @file
 * @author Dan Nixon
 */

#include "IState.h"

namespace Simulation
{
namespace AI
{
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
   * @return State tree branch
   */
  std::vector<IState *> IState::branch()
  {
    std::vector<IState *> branch;

    IState *node = this;
    while (node != nullptr)
    {
      branch.push_back(dynamic_cast<IState *>(node));
      node = node->m_parent;
    }

    std::reverse(branch.begin(), branch.end());

    return branch;
  }

  /**
   * @brief Sets the activation of this state.
   * @param active If this state is active or not
   */
  void IState::setActivation(bool active)
  {
    if (!active)
      onExit();

    IState *node = this;
    while (node != nullptr && node->m_parent != nullptr)
    {
      node->m_parent->m_active = active ? node : nullptr;
      node = node->m_parent;
    }

    if (active)
      onEntry();
  }
}
}
