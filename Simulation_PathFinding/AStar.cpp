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
      QueueableNode * p = m_openList.top();

      // Check if this is the ned node
      if (p->node == end)
      {
        success = true;
        break;
      }

      // Move this node to the closed list
      m_openList.pop();
      m_closedList.push_back(p);

      // For each node connected to the next node
      for (size_t i = 0; i < p->node->numConnections(); i++)
      {
        Edge * pq = p->node->edge(i);
        QueueableNode * q = m_nodeData[pq->otherNode(p->node)];

        // Calculate new scores
        float gScore = p->gScore + pq->cost();
        float fScore = gScore + q->node->h(*end);
   
        // Search for this node on open and closed lists
        auto closedIt = std::find(m_closedList.begin(), m_closedList.end(), q);
        auto openIt = m_openList.find(q);

        if (closedIt != m_closedList.end() || openIt != m_openList.end())
        {
          // Check if this path is more efficient that the previous best
          if (q->gScore > gScore)
          {
            q->parent = p;
            q->gScore = gScore;
            q->fScore = fScore;
          }
        }
        else
        {
          // Add this path to the open list if it has yet to be considered
          q->parent = p;
          q->gScore = gScore;
          q->fScore = fScore;
          m_openList.push(q);
        }
      }
    }

    // If successful then reconstruct the best path
    if (success)
    {
      // Add nodes to path
      QueueableNode * n = m_closedList.back();
      while (n)
      {
        m_path.push_back(n->node);
        n = n->parent;
      }

      // Reverse path to be ordered start to end
      std::reverse(m_path.begin(), m_path.end());
    }

    return success;
  }
}
}
