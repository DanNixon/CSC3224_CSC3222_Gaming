/**
 * @file
 * @author Dan Nixon
 */

#include "StateMachine.h"

namespace Simulation
{
namespace AI
{
  StateMachine::StateMachine()
  {
  }

  StateMachine::~StateMachine()
  {
  }

  /**
   * @brief Gets the active branch of the state tree.
   * @return Branch of active states
   */
  std::vector<State *> StateMachine::activeStateBranch()
  {
    std::vector<State *> branch;

    State *node = activeChild();
    while (node != nullptr)
    {
      branch.push_back(node);
      node = node->activeChild();
    }

    return branch;
  }

  /**
   * @brief Performs transfer checks for each level of the active state branch
   *        and switches states if needed.
   */
  void StateMachine::transfer()
  {
    // TODO
  }

  /**
   * @brief Performs operations associated with the currently active branch of
   *        the state tree.
   */
  void StateMachine::operate()
  {
    State *node = activeChild();
    while (node != nullptr)
    {
      node->onOperate();
      node = node->activeChild();
    }
  }
}
}
