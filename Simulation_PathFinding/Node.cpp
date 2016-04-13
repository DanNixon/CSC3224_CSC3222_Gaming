/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "Node.h"

#include <string>
#include <vector>

#include "Edge.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace PathFinding
{
  /**
   * @brief Creates a new node.
   * @param id String ID
   * @param position Position of the node in 3 dimensions
   */
  Node::Node(const std::string &id, const Vector3 &position)
      : m_id(id)
      , m_position(position)
  {
  }

  /**
   * Copy constructor.
   * @param n Other node
   */
  Node::Node(const Node &n)
      : m_id(n.m_id)
      , m_position(n.m_position)
  {
  }

  Node::~Node()
  {
  }

  /**
   * @brief Outputs a Node to a stream.
   * @param stream Stream to output to
   * @param n Node to output
   * @return Reference to stream
   */
  std::ostream &operator<<(std::ostream &stream, const Node &n)
  {
    stream << n.m_id << ":" << n.m_position;
    return stream;
  }

  /**
   * @brief Parses node data from a stream.
   * @param stream Stream to parse from
   * @param n Node to set
   * @return Reference to stream
   */
  std::istream &operator>>(std::istream &stream, Node &n)
  {
    const int len = 100;

    // Allow colons to be a delimiter
    const auto classic = std::ctype<char>::classic_table();
    std::vector<std::ctype<char>::mask> delims(classic, classic + std::ctype<char>::table_size);
    delims[':'] = std::ctype_base::space;

    // Set new delimiter configuration
    stream.imbue(std::locale(stream.getloc(), new std::ctype<char>(delims.data())));

    std::string id;
    Vector3 position;

    stream >> id;
    stream >> position;

    // Reset delimiter configuration
    stream.imbue(std::locale(stream.getloc(), new std::ctype<char>));

    n = Node(id, position);

    return stream;
  }
}
}
