/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "Edge.h"

#include <string>

namespace Simulation
{
namespace PathFinding
{
  /**
   * @brief Creates a new edge.
   * @param a First node
   * @param b Second node
   * @param id Optional string ID
   */
  Edge::Edge(Node *a, Node *b, const std::string &id)
      : m_id(id)
      , m_nodeA(a)
      , m_nodeB(b)
      , m_traversable(true)
      , m_weight(1.0f)
  {
    // Default ID based on node IDs
    if (id.empty())
      m_id = a->id() + "-" + b->id();

    // Associate this edge with the nodes
    m_nodeA->m_connections.push_back(this);
    m_nodeB->m_connections.push_back(this);
  }

  Edge::~Edge()
  {
  }

  /**
   * @brief Sets if this edge can be traversed.
   * @param traversable True if this edge can be traversed
   */
  void Edge::setTraversable(bool traversable)
  {
    m_traversable = traversable;
  }

  /**
   * @brief Sets the traversal weighting of this edge.
   * @param weight Edge weight
   */
  void Edge::setWeight(float weight)
  {
    m_weight = weight;
  }

  /**
   * @brief Outputs an Edge to a stream.
   * @param stream Stream to output to
   * @param e Edge to output
   * @return Reference to stream
   */
  std::ostream &operator<<(std::ostream &stream, const Edge &e)
  {
    stream << "Edge(id=" << e.m_id << ",a=" << e.m_nodeA->id() << ",b=" << e.m_nodeB->id() << ")";
    return stream;
  }
}
}
