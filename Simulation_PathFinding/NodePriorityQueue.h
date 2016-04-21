/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_PRIORITYQUEUE_H_
#define _SIMULATION_PATHFINDING_PRIORITYQUEUE_H_

#include <functional>
#include <queue>

#include "Node.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @typedef NodePriorityQueueSuperType
   * @brief Underlaying queue type used for NodePriorityQueue.
   */
  typedef std::priority_queue<QueueableNode *, std::vector<QueueableNode *>, std::greater<QueueableNode *>> NodePriorityQueueSuperType;

  /**
   * @class NodePriorityQueue
   * @brief Wrapper around a priority queue that can test for presence of a node.
   * @author Dan Nixon
   */
  class NodePriorityQueue : public NodePriorityQueueSuperType
  {
  public:
    typedef NodePriorityQueueSuperType::container_type::iterator iterator;

    iterator begin()
    {
      return this->c.begin();
    }

    iterator end()
    {
      return this->c.end();
    }

    /**
     * @brief Searches for a given node in the queue.
     * @param node Node to search for
     * @return Iterator at which the node was found, end if not found
     */
    iterator findNode(Node * node)
    {
      auto first = this->c.begin();
      auto last = this->c.end();

      // Iterate through storage
      while (first != last)
      {
        if ((*first)->node == node)
          return first;

        ++first;
      }

      return last;
    }
  };
}
}

#endif
