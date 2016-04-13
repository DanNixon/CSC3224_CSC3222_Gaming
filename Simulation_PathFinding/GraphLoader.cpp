/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "GraphLoader.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

#include <Engine_Logging/Logger.h>

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

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
    g_log.trace("Loading graph from file: " + filepath);

    // Open file
    std::ifstream file;
    file.open(filepath);

    // Check if the file is open
    if ((file.rdstate() & std::ifstream::failbit) != 0)
    {
      g_log.warn("Cannot open file");
      return false;
    }

    // Load graph from stream
    bool result = LoadGraph(nodes, edges, file);

    // Close file
    file.close();

    return result;
  }

  /**
   * @brief Loads a graph from an input stream.
   * @param nodes Reference to vector of nodes
   * @param edges Reference to vector of edges
   * @param stream Stream to load data from
   * @return True if load was successful
   */
  bool GraphLoader::LoadGraph(std::vector<Node *> &nodes, std::vector<Edge *> &edges, std::istream &stream)
  {
    bool retVal = true;

    std::string line;
    std::getline(stream, line);
    while ((stream.rdstate() & std::istream::eofbit) == 0)
    {
      if (line.find("BEGIN") != std::string::npos)
      {
        // Check if this line is a node hdeader
        if (line.find("NODES") != std::string::npos)
        {
          g_log.debug("Found start of node block");
          if (!LoadNodes(nodes, stream))
            retVal = false;
        }
        // Check if this line is an edge header
        else if (line.find("EDGES") != std::string::npos)
        {
          g_log.debug("Found start of edge block");
          if (!LoadEdges(nodes, edges, stream))
            retVal = false;
        }
      }

      std::getline(stream, line);
    }

    return retVal;
  }

  /**
   * @brief Loads nodes from an input stream.
   * @param nodes Reference to vector of nodes
   * @param stream Stream to load data from
   * @return True if load was successful
   */
  bool GraphLoader::LoadNodes(std::vector<Node *> &nodes, std::istream &stream)
  {
    bool retVal = false;

    std::string line;
    std::getline(stream, line);
    while ((stream.rdstate() & std::istream::eofbit) == 0)
    {
      // Check for end of block
      if (line.find("END") != std::string::npos)
        break;

      // Parse node
      Node n("");
      std::istringstream str(line);
      str >> n;

      // Ignore lines that generated parse errors
      if ((str.rdstate() & std::istringstream::failbit) == 0)
      {
        nodes.push_back(new Node(n));
        retVal = true;
      }

      // Read next line
      std::getline(stream, line);
    }

    return retVal;
  }

  /**
   * @brief Loads edges from an input stream.
   * @param nodes Reference to vector of nodes
   * @param edges Reference to vector of edges
   * @param stream Stream to load data from
   * @return True if load was successful
   */
  bool GraphLoader::LoadEdges(std::vector<Node *> &nodes, std::vector<Edge *> &edges, std::istream &stream)
  {
    bool retVal = true;

    // Allow colons and commas to be a delimiter
    const auto classic = std::ctype<char>::classic_table();
    std::vector<std::ctype<char>::mask> delims(classic, classic + std::ctype<char>::table_size);
    delims[':'] = std::ctype_base::space;
    delims[','] = std::ctype_base::space;

    std::string line;
    std::getline(stream, line);
    while ((stream.rdstate() & std::istream::eofbit) == 0)
    {
      // Check for end of block
      if (line.find("END") != std::string::npos)
        break;

      std::istringstream str(line);

      // Set new delimiter configuration
      str.imbue(std::locale(stream.getloc(), new std::ctype<char>(delims.data())));

      std::string id, nodeAName, nodeBName;
      str >> id;
      str >> nodeAName;
      str >> nodeBName;

      // Reset delimiter configuration
      str.imbue(std::locale(stream.getloc(), new std::ctype<char>));

      // Ignore lines that generated parse errors
      if ((str.rdstate() & std::istringstream::failbit) == 0)
      {
        auto nodeA = std::find_if(nodes.begin(), nodes.end(), [&nodeAName](Node *n) { return n->id() == nodeAName; });
        auto nodeB = std::find_if(nodes.begin(), nodes.end(), [&nodeBName](Node *n) { return n->id() == nodeBName; });

        // Ignore if either node cannot be found
        if ((nodeA != nodes.end()) && (nodeB != nodes.end()))
        {
          Edge *e = new Edge(*nodeA, *nodeB, id);
          edges.push_back(e);
        }
        else
        {
          g_log.warn("At least one node not found for edge: " + id);
          retVal = false;
        }
      }

      // Read next line
      std::getline(stream, line);
    }

    return retVal;
  }
}
}
