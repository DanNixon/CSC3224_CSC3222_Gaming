/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_ASTAR_H_
#define _SIMULATION_PATHFINDING_ASTAR_H_

#include <functional>
#include <map>
#include <queue>
#include <vector>

#include "Node.h"
#include "QueueableNode.h"

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
    /**
     * @typedef NodePriorityQueue
     * @brief Priority queue type for open and closed lists.
     */
    typedef std::priority_queue<QueueableNode, std::vector<QueueableNode>, std::greater<QueueableNode>>
        NodePriorityQueue;

  public:
    AStar();
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
    NodePriorityQueue closedList() const
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
    std::map<Node *, float> m_gValues; //!< Cache of calculated g values

    NodePriorityQueue m_openList;   //!< Open list
    NodePriorityQueue m_closedList; //!< Closed list

    std::vector<Node *> m_path; //!< Computed path
  };
}
}

#endif
