/**
 * @file
 * @author Dan Nixon
 */

#include "INIKeyValueStore.h"

#include "KVNode.h"

namespace Engine
{
namespace IO
{
  INIKeyValueStore::INIKeyValueStore()
  {
  }

  INIKeyValueStore::~INIKeyValueStore()
  {
  }

  /**
   * @copydoc IKeyValueStore::load
   */
  bool INIKeyValueStore::load(std::istream &stream)
  {
    parseNode(stream, m_root, true);

    while (!stream.eof())
    {
      KVNode node;
      parseNode(stream, node);
      m_root.addChild(node);
    }

    return true;
  }

  /**
   * @copydoc IKeyValueStore::save
   */
  bool INIKeyValueStore::save(std::ostream &stream)
  {
    outputNode(stream, m_root);

    for (auto it = m_root.m_children.begin(); it != m_root.m_children.end(); ++it)
      outputNode(stream, it->second);

    return true;
  }

  void INIKeyValueStore::parseNode(std::istream &stream, KVNode &node, bool root)
  {
    const auto n = std::numeric_limits<std::streamsize>::max();
    std::string name;

    if (!root)
    {
      stream.ignore(n, '[');
      std::getline(stream, name);
      name.erase(name.find_last_not_of("[]") + 1);
    }

    node = KVNode(name);

    while (stream.peek() != '[' && !stream.eof())
    {
      std::string line;
      std::getline(stream, line);
      size_t eqPos = line.find("=");
      if (eqPos != -1)
      {
        std::string key = line.substr(0, eqPos);
        key.erase(key.find_last_not_of(" \n\r\t") + 1);

        std::string value = line.substr(eqPos + 1);
        value.erase(value.find_last_not_of(" \n\r\t") + 1);

        node.set(key, value);
      }
    }
  }

  void INIKeyValueStore::outputNode(std::ostream &stream, const KVNode &node)
  {
    if (!node.name().empty())
      stream << "[" << node.name() << "]" << std::endl;

    for (auto it = node.m_keys.begin(); it != node.m_keys.end(); ++it)
      stream << it->first << "=" << it->second << std::endl;
  }
}
}
