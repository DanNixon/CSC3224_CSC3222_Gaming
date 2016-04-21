/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_ASTAR_H_
#define _SIMULATION_PATHFINDING_ASTAR_H_

#include <map>
#include <vector>

#include "Node.h"
#include "QueueableNode.h"
#include "NodePriorityQueue.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @class AStar
   * @brief Implementaton of the A* path finding algorithm.
   * @author Dan Nixon
   */
  class AStar
  {
  public:
    AStar(const std::vector<Node *> &nodes);
    virtual ~AStar();

    void reset();
    bool findPath(Node *start, Node *end);

    /**
     * @brief Gets the open list.
     * @return Open list
     */
    NodePriorityQueue openList() const
    {
      return m_openList;
    }

    /**
     * @brief Gets the closed list.
     * @return Closed list
     */
    std::vector<QueueableNode> closedList() const
    {
      return m_closedList;
    }

    /**
     * @brief Gets the computed path.
     * @return Path
     */
    std::vector<Node *> path() const
    {
      return m_path;
    }

  private:
    std::map<Node *, QueueableNode *> m_nodeData;

    NodePriorityQueue m_openList;            //!< Open list
    std::vector<QueueableNode> m_closedList; //!< Closed list

    std::vector<Node *> m_path; //!< Computed path
  };
}
}

#endif
