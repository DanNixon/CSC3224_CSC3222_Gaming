/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_NODE_H_
#define _SIMULATION_PATHFINDING_NODE_H_

#include <vector>

namespace Simulation
{
namespace PathFinding
{
  class Arc;

  /**
   * @class Node
   * @brief Represents a node in a map.
   * @author Dan Nixon
   */
  class Node
  {
  public:
    Node(const std::string &id);
    virtual ~Node();

    /**
     * @brief Gets the ID of the node.
     * @retrun String ID
     */
    inline std::string id() const
    {
      return m_id;
    }

  private:
    friend class Edge;

    const std::string m_id;            //!< String ID of the node
    std::vector<Edge *> m_connections; //!< Edges of this node
  };
}
}

#endif