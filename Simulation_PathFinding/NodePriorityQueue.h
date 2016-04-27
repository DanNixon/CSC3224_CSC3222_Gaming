/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_PRIORITYQUEUE_H_
#define _SIMULATION_PATHFINDING_PRIORITYQUEUE_H_

#include <set>

#include "QueueableNode.h"
#include "less_ptr.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @typedef NodePriorityQueueSuperType
   * @brief Underlaying queue type used for NodePriorityQueue.
   */
  typedef std::set<QueueableNode *, less_ptr<QueueableNode>> NodePriorityQueueSuperType;

  /**
   * @class NodePriorityQueue
   * @brief Wrapper around a set that can emulate a priority queue.
   * @author Dan Nixon
   */
  class NodePriorityQueue : public NodePriorityQueueSuperType
  {
  public:
    void push(QueueableNode *item)
    {
      this->insert(item);
    }

    QueueableNode *top()
    {
      return *(this->begin());
    }

    QueueableNode *pop()
    {
      auto bIt = this->begin();
      QueueableNode *node = *bIt;
      erase(bIt);
      return node;
    }

    void updatePosition(QueueableNode *node)
    {
      auto it = std::find(begin(), end(), node);
      if (it != end())
      {
        erase(it);
        insert(node);
      }
    }
  };
}
}

#endif
