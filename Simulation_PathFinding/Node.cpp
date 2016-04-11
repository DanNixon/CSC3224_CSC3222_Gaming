/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "Node.h"

#include "Edge.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @brief Creates a new node.
   * @param id String ID
   */
  Node::Node(const std::string &id)
      : m_id(id)
  {
  }

  Node::~Node()
  {
  }
}
}
