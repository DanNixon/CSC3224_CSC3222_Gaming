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
   * @brief Wrapper around a vector that provides a priority queue.
   * @author Dan Nixon
   */
  class NodePriorityQueue : public std::vector<QueueableNode *>
  {
  public:
    /**
     * @brief Creates a new queue.
     */
    NodePriorityQueue()
        : std::vector<QueueableNode *>()
        , m_comp()
    {
      std::make_heap(begin(), end(), m_comp);
    }

    /**
     * @brief Adds a new node to the queue.
     * @param item Node to add
     */
    void push(QueueableNode *item)
    {
      push_back(item);
      std::push_heap(begin(), end(), m_comp);
    }

    /**
     * @brief Removes the node at the top of the list.
     */
    void pop()
    {
      std::pop_heap(begin(), end(), m_comp);
      pop_back();
    }

    /**
     * @brief Returns the node at the top of the list.
     * @return Highest node
     */
    QueueableNode *top() const
    {
      return front();
    }

    /**
     * @brief Searches for a node in the queue.
     * @param item Node to find
     * @return Const iterator to item
     */
    std::vector<QueueableNode *>::const_iterator find(QueueableNode *item) const
    {
      return std::find(cbegin(), cend(), item);
    }

    /**
     * @brief Updates positions of nodes in the queue to preserve the queue
     *        priority.
     */
    void update()
    {
      std::make_heap(begin(), end(), m_comp);
    }

  private:
    greater_ptr<QueueableNode> m_comp; //!< Sorting comparator
  };
}
}

#endif
