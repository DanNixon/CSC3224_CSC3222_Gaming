/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "GraphLoader.h"

#include <fstream>

namespace Simulation
{
namespace PathFinding
{
  /**
   * @brief Loads a graph from a file given the path to the file.
   * @param nodes Reference to vector of nodes
   * @param edges Reference to vector of edges
   * @param filepath Path to data file
   * @return True if load was successful
   */
  bool GraphLoader::LoadGraph(std::vector<Node *> &nodes, std::vector<Edge *> &edges, const std::string &filepath)
  {
    std::ifstream file;
    file.open(filepath);
    bool result = LoadGraph(nodes, edges, file);
    file.close();
    return result;
  }

  /**
   * @brief Loads a graph from an input stream.
   * @param nodes Reference to vector of nodes
   * @param edges Reference to vector of edges
   * @param stream STream to load data from
   * @return True if load was successful
   */
  bool GraphLoader::LoadGraph(std::vector<Node *> &nodes, std::vector<Edge *> &edges, std::istream &stream)
  {
    // TODO
    return false;
  }

  /**
   * @brief Loads nodes from an input stream.
   * @param nodes Reference to vector of nodes
   * @param stream STream to load data from
   * @return True if load was successful
   */
  bool GraphLoader::LoadNodes(std::vector<Node *> &nodes, std::istream &stream)
  {
    // TODO
    return false;
  }

  /**
   * @brief Loads edges from an input stream.
   * @param edges Reference to vector of edges
   * @param stream STream to load data from
   * @return True if load was successful
   */
  bool GraphLoader::LoadEdges(std::vector<Edge *> &edges, std::istream &stream)
  {
    // TODO
    return false;
  }
}
}
