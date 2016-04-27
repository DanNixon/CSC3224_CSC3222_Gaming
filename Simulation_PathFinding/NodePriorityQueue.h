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
   * @brief Wrapper around a priority queue that can test for presence of a node.
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
      QueueableNode *node = *(this->begin());
      return node;
    }

    QueueableNode *pop()
    {
      QueueableNode *node = *(this->begin());
      erase(this->begin());
      return node;
    }

    void update(QueueableNode *node)
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
