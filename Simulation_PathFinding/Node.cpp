/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "Node.h"

#include <string>

#include "Edge.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace PathFinding
{
  /**
   * @brief Creates a new node.
   * @param id String ID
   * @param position Position of the node in 3 dimensions
   */
  Node::Node(const std::string &id, const Vector3 &position)
      : m_id(id)
      , m_position(position)
  {
  }

  Node::~Node()
  {
  }

  /**
   * @brief Outputs a Node to a stream.
   * @param stream Stream to output to
   * @param n Node to output
   * @return Reference to stream
   */
  std::ostream &operator<<(std::ostream &stream, const Node &n)
  {
    stream << "Node(id=" << n.m_id << ", position=" << n.m_position << ")";
    return stream;
  }
}
}
