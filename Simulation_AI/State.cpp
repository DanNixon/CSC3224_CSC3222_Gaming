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
   * @param parent Parent state
   */
  State::State(const std::string &name, State *parent)
      : m_name(name)
      , m_parent(parent)
  {
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

    State * node = this;
    while(node != nullptr)
    {
      branch.push_back(node);
      node = node->m_parent;
    }

    std::reverse(branch.begin(), branch.end());

    return branch;
  }
}
}
