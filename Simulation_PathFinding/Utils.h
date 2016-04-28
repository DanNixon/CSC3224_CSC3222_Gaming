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
  class Utils
  {
  public:
    static bool IsOnList(const std::vector<QueueableNode *> &list, Node *node)
    {
      return std::find_if(list.begin(), list.end(), [node](QueueableNode *n) { return n->node == node; }) != list.end();
    }

    static bool IsOnList(const std::vector<Node *> &list, Node *node)
    {
      return std::find(list.begin(), list.end(), node) != list.end();
    }

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
