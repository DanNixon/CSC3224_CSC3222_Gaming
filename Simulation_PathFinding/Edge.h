/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_ARC_H_
#define _SIMULATION_PATHFINDING_ARC_H_

#include "Node.h"

#include <Engine_Maths/VectorOperations.h>

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
     * @return String ID
     */
    inline std::string id() const
    {
      return m_id;
    }

    /**
     * @brief Gets the first node.
     * @return First node
     */
    inline Node *nodeA()
    {
      return m_nodeA;
    }

    /**
     * @brief Gets the second node.
     * @return Second node
     */
    inline Node *nodeB()
    {
      return m_nodeB;
    }

    Node *otherNode(Node *node);

    /**
     * @brief Tests if this edge is traversable.
     * @return True if this edge can be traversed
     */
    inline bool traversable() const
    {
      return m_traversable;
    }

    /**
     * @brief Gets the static cost of traversing this edge.
     * @return Static cost
     */
    inline float staticCost() const
    {
      return Engine::Maths::VectorOperations::Distance2(m_nodeA->position(), m_nodeB->position());
    }

    /**
     * @brief Gets the weight coefficient of traversing this edge.
     * @return Edge weight
     */
    inline float weight() const
    {
      return m_weight;
    }

    /**
     * @brief Gets the weighted cost of traversing this edge.
     * @return Weighted cost
     */
    inline float cost() const
    {
      return staticCost() * m_weight;
    }

    void setTraversable(bool traversable);
    void setWeight(float weight);

    bool operator==(const Edge &other) const;
    bool operator!=(const Edge &other) const;

    friend std::ostream &operator<<(std::ostream &stream, const Edge &e);

  private:
    std::string m_id; //!< String ID of the edge
    Node *m_nodeA;    //!< First node
    Node *m_nodeB;    //!< Second node

  protected:
    bool m_traversable; //!< Flag indicating if this edge can be traversed
    float m_weight;     //!< Weight coefficient of traversing this edge
  };
}
}

#endif
