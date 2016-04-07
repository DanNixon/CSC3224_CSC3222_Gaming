/**
 * @file
 * @author Dan Nixon
 */

#include "StateContainer.h"

#include <algorithm>

#include <Engine_Utility/StringUtils.h>

#include "State.h"

using namespace Engine::Utility;

namespace Simulation
{
namespace AI
{
  StateContainer::StateContainer()
      : m_active(nullptr)
  {
  }

  StateContainer::~StateContainer()
  {
  }

  /**
   * @brief Finds a state in this sub tree given its path.
   * @name Path to state
   * @return State branch
   */
  std::vector<State *> StateContainer::findState(const std::string &name, char delim)
  {
    std::vector<State *> branch;
    std::vector<std::string> names = StringUtils::Split(name, delim);
    std::reverse(names.begin(), names.end());

    findStateImpl(names, branch);

    return branch;
  }

  /**
   * @brief Performs recursive search for a state within this sub tree.
   * @param names Reference to vector of names of states in branch in reverse
   *              order
   * @param branch Reference to the vector containing branch states
   * @return True if search was succesfull
   */
  bool StateContainer::findStateImpl(std::vector<std::string> &names, std::vector<State *> &branch)
  {
    // Find child by name
    const std::string name(names.back());
    auto it = std::find_if(m_children.begin(), m_children.end(), [name](State *i) { return i->name() == name; });

    // Fail if child not found
    if (it == m_children.end())
      return false;

    // Remove found name and add found state
    branch.push_back(*it);
    names.pop_back();

    // If found sttae has children and there are still names to find then search further
    if ((*it)->hasChildren() && !names.empty())
      return (*it)->findStateImpl(names, branch);
    else
      return true;
  }
}
}