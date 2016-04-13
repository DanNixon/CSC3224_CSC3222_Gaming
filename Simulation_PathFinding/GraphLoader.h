/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#ifndef _SIMULATION_PATHFINDING_GRAPHLOADER_H_
#define _SIMULATION_PATHFINDING_GRAPHLOADER_H_

#include <vector>

#include "Edge.h"
#include "Node.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @class GraphLoader
   * @brief Loads Nodes and Edges from an ASCII data file to make up a graph.
   * @author Dan Nixon
   */
  class GraphLoader
  {
  public:
    static bool LoadGraph(std::vector<Node *> &nodes, std::vector<Edge *> &edges, const std::string &filepath);
    static bool LoadGraph(std::vector<Node *> &nodes, std::vector<Edge *> &edges, std::istream &stream);

    static bool LoadNodes(std::vector<Node *> &nodes, std::istream &stream);
    static bool LoadEdges(std::vector<Node *> &nodes, std::vector<Edge *> &edges, std::istream &stream);
  };
}
}

#endif