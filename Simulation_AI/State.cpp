/**
 * @file
 * @author Dan Nixon
 */

#include "State.h"

namespace Simulation
{
namespace AI
{
  State::State(State *parent)
      : m_parent(parent)
  {
    parent->m_children.push_back(this);
  }

  State::~State()
  {
  }
}
}
