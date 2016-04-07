/**
 * @file
 * @author Dan Nixon
 */

#include "StateMachine.h"

#include <sstream>

namespace Simulation
{
namespace AI
{
  /**
   * @brief Outputs a state branch as a string.
   * @param branch State branch
   * @param delim Delimiter
   * @return Delimited names of states in branch
   */
  std::string StateMachine::BranchToString(const std::vector<State *> &branch, char delim)
  {
    std::stringstream str;
    for (auto it = branch.begin(); it != branch.end(); ++it)
    {
      if (it != branch.begin())
        str << delim;

      str << (*it)->m_name;
    }

    return str.str();
  }

  StateMachine::StateMachine()
      : m_root("", nullptr, this)
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

    State *node = m_root.activeChild();
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
   * @return True if a state change took place
   */
  bool StateMachine::transfer()
  {
    std::vector<State *> branch = activeStateBranch();
    bool stateChange = false;

    for (auto it = branch.begin(); it != branch.end(); ++it)
    {
      State *transferState = (*it)->testTransferCase();
      if (transferState != nullptr)
      {
        stateChange = true;

        // TODO: find a better way to do this (this causes issues with onEntry and onExit
        branch.back()->setActivation(false);
        transferState->setActivation(true);

        break;
      }
    }

    return stateChange;
  }

  /**
   * @brief Performs operations associated with the currently active branch of
   *        the state tree.
   */
  void StateMachine::operate()
  {
    State *node = m_root.activeChild();
    while (node != nullptr)
    {
      node->onOperate();
      node = node->activeChild();
    }
  }
}
}
