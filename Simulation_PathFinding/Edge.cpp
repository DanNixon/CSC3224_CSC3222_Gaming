/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "Edge.h"

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
}
}
