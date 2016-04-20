/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "AStar.h"

namespace Simulation
{
namespace PathFinding
{
  AStar::AStar()
  {
  }

  AStar::~AStar()
  {
  }

  /**
   * @brief Clears open and closed lists and computed path.
   */
  void AStar::reset()
  {
    m_gValues.clear();
    m_openList = NodePriorityQueue();
    m_closedList = NodePriorityQueue();
    m_path.clear();
  }

  /**
   * @brief Finds the shortest path between two nodes.
   * @param start Starting node
   * @param end Target node
   * @return True if path finding was successful
   */
  bool AStar::findPath(Node *start, Node *end)
  {
    // Clear caches
    reset();

    // Add start node to open list
    QueueableNode startNode(start, 0.0f);
    m_openList.push(startNode);

    bool success = false;
    while (!m_openList.empty())
    {
      QueueableNode next = m_openList.top();

      // Check if this is the ned node
      if (next.node == end)
      {
        success = true;
        break;
      }

      // Move this node to the closed list
      m_openList.pop();
      m_closedList.push(next);

      // next.node->
    }

    // If successful then reconstruct the best path
    if (success)
    {
      // TODO
    }

    return success;
  }
}
}
