/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_PRIORITYQUEUE_H_
#define _SIMULATION_PATHFINDING_PRIORITYQUEUE_H_

#include <algorithm>

#include "QueueableNode.h"
#include "greater_ptr.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @class NodePriorityQueue
   * @brief Wrapper around a set that can emulate a priority queue.
   * @author Dan Nixon
   */
  class NodePriorityQueue : public std::vector<QueueableNode *>
  {
  public:
    NodePriorityQueue() :
      std::vector<QueueableNode *>(),
      m_comp()
    {
      std::make_heap(begin(), end(), m_comp);
    }

    void push(QueueableNode * item)
    {
      push_back(item);
      std::push_heap(begin(), end(), m_comp);
    }

    void pop()
    {
      std::pop_heap(begin(), end(), m_comp);
      pop_back();
    }

    QueueableNode * top() const
    {
      return front();
    }

    std::vector<QueueableNode *>::const_iterator find(QueueableNode * item) const
    {
      return std::find(cbegin(), cend(), item);
    }

    void update()
    {
      std::make_heap(begin(), end(), m_comp);
    }

  private:
    greater_ptr<QueueableNode> m_comp;
  };
}
}

#endif
