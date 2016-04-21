/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_QUEUEABLENODE_H_
#define _SIMULATION_PATHFINDING_QUEUEABLENODE_H_

#include <vector>

#include <Engine_Maths/Vector3.h>

#include "Node.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @class QueueableNode
   * @brief Wrapper around a Node for use in AStar.
   * @author Dan Nixon
   *
   * Contains comparators for priority queue and a pointer to a parent node.
   */
  class QueueableNode
  {
  public:
    /**
     * @brief Creates a new wrapper.
     * @param n Wrapped node
     */
    QueueableNode(Node *n)
        : node(n)
        , parent(nullptr)
        , fScore(std::numeric_limits<float>::max())
        , gScore(std::numeric_limits<float>::max())
    {
    }

    virtual ~QueueableNode()
    {
    }

    /**
     * @brief Tests for difference between F values of this node and another.
     * @param other Node wrapper being compared with
     * @return True if this node has an F value greater than than that of
     *         other.
     */
    bool operator>(const QueueableNode &other) const
    {
      return this->fScore > other.fScore;
    }

    /**
     * @brief Tests for difference between F values of this node and another.
     * @param other Node wrapper being compared with
     * @return True if this node has an F value greater than of equal to that
     *         of other.
     */
    bool operator>=(const QueueableNode &other) const
    {
      return this->fScore >= other.fScore;
    }

    /**
     * @brief Tests for difference between F values of this node and another.
     * @param other Node wrapper being compared with
     * @return True if this node has an F value less than that of other.
     */
    bool operator<(const QueueableNode &other) const
    {
      return this->fScore < other.fScore;
    }

    /**
     * @brief Tests for difference between F values of this node and another.
     * @param other Node wrapper being compared with
     * @return True if this node has an F value less than or equal to that of
     *         other.
     */
    bool operator<=(const QueueableNode &other) const
    {
      return this->fScore <= other.fScore;
    }

  public:
    Node *node;            //!< Wrapped Node
    QueueableNode *parent; //!< Parent Node in path
    float fScore;          //!< F score of wrapped node
    float gScore;          //!< G score of wrapped node
  };
}
}

#endif
