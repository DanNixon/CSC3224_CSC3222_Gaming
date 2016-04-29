/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_UTILS_H_
#define _SIMULATION_PATHFINDING_UTILS_H_

#include <algorithm>
#include <vector>

#include "Edge.h"
#include "QueueableNode.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @class Utils
   * @brief Utility methods for path finding.
   * @author Dan Nixon
   */
  class Utils
  {
  public:
    /**
     * @brief Checks if a QueueableNode is on a given list.
     * @param list List to check
     * @param node Node to search for
     * @return True if node was found on list
     */
    static bool IsOnList(const std::vector<QueueableNode *> &list, Node *node)
    {
      return std::find_if(list.begin(), list.end(), [node](QueueableNode *n) { return n->node == node; }) != list.end();
    }

    /**
     * @brief Checks if a Node is on a given list.
     * @param list List to check
     * @param node Node to search for
     * @return True if node was found on list
     */
    static bool IsOnList(const std::vector<Node *> &list, Node *node)
    {
      return std::find(list.begin(), list.end(), node) != list.end();
    }

    /**
     * @brief Cecks of an Edge is on a path.
     * @param path Path to check
     * @param edge Edge to test
     * @return True if edge is on the path
     *
     * Edges are on a path if both nodes are on the path and are a distance of
     * 1 apart.
     */
    static bool IsOnPath(const std::vector<Node *> &path, Edge *edge)
    {
      auto aIt = std::find(path.begin(), path.end(), edge->nodeA());
      auto bIt = std::find(path.begin(), path.end(), edge->nodeB());
      return (aIt != path.end() && bIt != path.end() && std::abs(std::distance(aIt, bIt)) == 1);
    }
  };
}
}

#endif
