/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_NODE_H_
#define _SIMULATION_PATHFINDING_NODE_H_

#include <vector>

#include <Engine_Maths/Vector3.h>
#include <Engine_Maths/VectorOperations.h>

namespace Simulation
{
namespace PathFinding
{
  class Edge;

  /**
   * @class Node
   * @brief Represents a node in a map.
   * @author Dan Nixon
   */
  class Node
  {
  public:
    Node(const std::string &id, const Engine::Maths::Vector3 &position = Engine::Maths::Vector3());
    Node(const Node &n);
    virtual ~Node();

    /**
     * @brief Gets the ID of the node.
     * @return String ID
     */
    inline std::string id() const
    {
      return m_id;
    }

    /**
     * @brief Gets the position of this node.
     * @return Node position
     */
    inline Engine::Maths::Vector3 position() const
    {
      return m_position;
    }

    /**
     * @brief Gets the number of connections from this node.
     * @return Number of connections
     */
    inline size_t numConnections() const
    {
      return m_connections.size();
    }

    /**
     * @brief Gets an edge connecting this node to another.
     * @param i Index of edge to retrieve
     * @return Pointer to edge
     */
    inline Edge *edge(size_t i)
    {
      return m_connections[i];
    }

    /**
     * @brief Gets the heuristic cost of traversing the path between this node
     *        and another.
     * @param other Other node
     * @return Heuristic cost
     *
     * Uses the square of the distance between nodes.
     */
    inline float h(const Node &other) const
    {
      return Engine::Maths::VectorOperations::Distance2(m_position, other.m_position);
    }

    friend std::ostream &operator<<(std::ostream &stream, const Node &n);

  private:
    friend class Edge;

    std::string m_id;                  //!< String ID of the node
    std::vector<Edge *> m_connections; //!< Edges of this node
    Engine::Maths::Vector3 m_position; //!< Posiion of this node
  };

  std::istream &operator>>(std::istream &stream, Node &n);
}
}

#endif
