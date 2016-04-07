/**
 * @file
 * @author Dan Nixon
 */

#include "State.h"

namespace Simulation
{
namespace AI
{
  /**
   * @brief Create a new state.
   * @param name Name of this state
   * @param parent Parent state
   */
  State::State(const std::string &name, State *parent)
      : m_name(name)
      , m_parent(parent)
  {
    if (parent)
      parent->m_children.push_back(this);
  }

  State::~State()
  {
  }

  /**
   * @brief Gets the branch of the state tree that leads to this node.
   * @return State tree branch
   */
  std::vector<State *> State::branch()
  {
    std::vector<State *> branch;

    State *node = this;
    while (node != nullptr)
    {
      branch.push_back(dynamic_cast<State *>(node));
      node = node->m_parent;
    }

    std::reverse(branch.begin(), branch.end());

    return branch;
  }

  /**
   * @brief Sets the activation of this state.
   * @param active If this state is active or not
   */
  void State::setActivation(bool active)
  {
    if (!active)
      onExit();

    State *node = this;
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
