/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "Node.h"

#include "Edge.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace PathFinding
{
  /**
   * @brief Creates a new node.
   * @param id String ID
   */
  Node::Node(const std::string &id, const Vector3 &position)
      : m_id(id)
      , m_position(position)
  {
  }

  Node::~Node()
  {
  }
}
}
