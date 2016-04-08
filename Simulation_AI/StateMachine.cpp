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
  std::string StateMachine::BranchToString(const IStatePtrList &branch, char delim)
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
  IStatePtrList StateMachine::activeStateBranch()
  {
    IStatePtrList branch;

    IState *node = m_root.activeChild();
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
    IStatePtrList branch = activeStateBranch();
    IState *oldState = branch.back();
    bool stateChange = false;

    for (IStatePtrListIter brIt = branch.begin(); brIt != branch.end(); ++brIt)
    {
      IState *transferState = (*brIt)->testTransferFrom();

      if (transferState == nullptr)
      {
        IStatePtrList siblings = (*brIt)->parent()->children();
        for (IStatePtrListIter sibIt = siblings.begin(); sibIt != siblings.end(); ++sibIt)
        {
          if ((*sibIt != *brIt) && (*sibIt)->testTransferTo())
          {
            transferState = *sibIt;
            break;
          }
        }
      }

      if (transferState != nullptr)
      {
        stateChange = true;

        IState *commonAncestor = IState::ClosestCommonAncestor(oldState, transferState);
        oldState->setActivation(false, commonAncestor);
        transferState->setActivation(true, commonAncestor);

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
    IState *node = m_root.activeChild();
    while (node != nullptr)
    {
      node->onOperate();
      node = node->activeChild();
    }
  }
}
}
