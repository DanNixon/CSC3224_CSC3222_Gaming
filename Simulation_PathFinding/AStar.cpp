/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "AStar.h"

#include "Edge.h"

namespace Simulation
{
namespace PathFinding
{
  /**
   * @brief CRetaes a new A* path planner.
   * @param nodes Vector of nodes in graph
   */
  AStar::AStar(const std::vector<Node *> &nodes)
  {
    // Create node data
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
      m_nodeData[*it] = new QueueableNode(*it);
  }

  AStar::~AStar()
  {
  }

  /**
   * @brief Clears open and closed lists and computed path and resets node
   *        data.
   */
  void AStar::reset()
  {
    // Clear caches
    m_openList = NodePriorityQueue();
    m_closedList.clear();
    m_path.clear();

    // Reset node data
    for (auto it = m_nodeData.begin(); it != m_nodeData.end(); ++it)
    {
      it->second->parent = nullptr;
      it->second->fScore = std::numeric_limits<float>::max();
      it->second->gScore = std::numeric_limits<float>::max();
    }
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
    m_nodeData[start]->gScore = 0.0f;
    m_nodeData[start]->fScore = m_nodeData[start]->node->h(*end);
    m_openList.push(m_nodeData[start]);

    bool success = false;
    while (!m_openList.empty())
    {
     // QueueableNode p = m_openList.top();

     // // Check if this is the ned node
     // if (p.node == end)
     // {
     //   success = true;
     //   break;
     // }

     // // Move this node to the closed list
     // m_openList.pop();
     // m_closedList.push_back(p);

	    //// For each node connected to the next node
	    //for (size_t i = 0; i < p.node->numConnections(); i++)
	    //{
     //   Edge * pq = p.node->edge(i);
     //   QueueableNode q(pq->otherNode(p.node));
     //   q.parent = p.node;

     //   // Calculate scores
     //   float gScore = m_gValues[p.node] + pq->cost();
     //   q.fValue = gScore + q.node->h(*end);

     //   // This path is no better
     //   if (m_gValues.find(q.node) != m_gValues.end() && m_gValues[q.node] < gScore)
     //     continue;
     //   
     //   auto closedIt = std::find_if(m_closedList.begin(), m_closedList.end(), [&q](QueueableNode & n){ return n.node == q.node; });
     //   auto openIt = m_openList.findNode(q.node);

     //   if (closedIt != m_closedList.end())
     //     closedIt->parent = p.node;
     //   else if (openIt != m_openList.end())
     //     openIt->parent = p.node;
     //   else
     //     m_openList.push(q);
  	  //}
    }

    // If successful then reconstruct the best path
    if (success)
    {
      //QueueableNode * n = m_closedList.back();
      //while (n.parent != nullptr)
      //{
      //  // TODO
      //}
    }

    return success;
  }
}
}
