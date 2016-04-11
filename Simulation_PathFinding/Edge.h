/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_ARC_H_
#define _SIMULATION_PATHFINDING_ARC_H_

#include "Node.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @class Edge
   * @brief Represents a connection between two nodes.
   * @author Dan Nixon
   */
  class Edge
  {
  public:
    Edge(Node *a, Node *b, const std::string &id = std::string());
    virtual ~Edge();

    /**
     * @brief Gets the ID of the arc.
     * @retrun String ID
     */
    inline std::string id() const
    {
      return m_id;
    }

    /**
     * @brief Tests if this edge is traversable.
     * @return True if this edge can be traversed
     */
    inline bool traversable() const
    {
      return m_traversable;
    }

    /**
     * @brief Gets the cost of traversing this edge.
     * @return Edge weight
     */
    inline float weight() const
    {
      return m_weight;
    }

  private:
    std::string m_id; //!< String ID of the edge
    Node *m_nodeA;    //!< First node
    Node *m_nodeB;    //!< Second node

  protected:
    bool m_traversable; //!< Flag indicating if this edge can be traversed
    float m_weight;     //!< Cost of traversing this edge
  };
}
}

#endif