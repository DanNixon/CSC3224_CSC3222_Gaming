/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_IO_KVNODE_H_
#define _ENGINE_IO_KVNODE_H_

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <Engine_Maths/Vector3.h>
#include <Engine_Utility/StringUtils.h>

namespace Engine
{
namespace IO
{
  /**
   * @class KVNode
   * @brief Represents a node in a key-value data store.
   * @author Dan Nixon
   *
   * Contains a set of key-value pairs and set of children.
   */
  class KVNode
  {
  public:
    /**
     * @brief Creates a new node.
     * @param name Name of this node (defaults to an empty name)
     *
     * Root nodes typically have an empty name.
     */
    KVNode(const std::string &name = "")
        : m_name(name)
    {
    }

    virtual ~KVNode()
    {
      m_keys.clear();
      m_children.clear();
    }

    /**
     * @brief Returns the name of this node.
     * @return Node name
     */
    std::string name() const
    {
      return m_name;
    }

    /** @name Key-Value pair functions
     *  @{
     */

    /**
     * @brief Returns the number of key-value pairs in this node.
     * @return Number of key-value pairs
     */
    size_t numKeys() const
    {
      return m_keys.size();
    }

    /**
     * @brief Checks to see if a key exists in this node.
     * @param key Key to test for
     * @return True if key exists
     */
    bool hasKey(const std::string &key) const
    {
      return (m_keys.find(key) != m_keys.end());
    }

    /**
     * @brief Returns the map of key values.
     * @return Reference to key map
     */
    std::map<std::string, std::string> &keys()
    {
      return m_keys;
    }

    std::string keyString(const std::string &name)
    {
      return m_keys[name];
    }

    float keyFloat(const std::string &name)
    {
      return std::stof(m_keys[name]);
    }

    bool keyBool(const std::string &name)
    {
      return Engine::Utility::StringUtils::ToBool(m_keys[name]);
    }

    Engine::Maths::Vector3 keyVector3(const std::string &name)
    {
      std::stringstream str(m_keys[name]);
      Engine::Maths::Vector3 vec;
      str >> vec;
      return vec;
    }

    /**
     * @brief Removes a key from the node.
     * @param key Key to remove
     * @return True if key was successfully removed
     */
    bool remove(const std::string &key)
    {
      return (m_keys.erase(key) == 1);
    }

    /** @} */

    /** @name Child node functions
     *  @{
     */

    /**
     * @brief Returns the number of child nodes of this node.
     * @return Number of child nodes
     */
    size_t numChildren() const
    {
      return m_children.size();
    }

    /**
     * @brief Checks to see if a child node with a given name exists in this
     *        node.
     * @param name Name of child node to test for
     * @return True if child exists
     */
    bool hasChild(const std::string &name) const
    {
      return (m_children.find(name) != m_children.end());
    }

    std::map<std::string, KVNode> &children()
    {
      return m_children;
    }

    void addChild(KVNode node)
    {
      m_children[node.name()] = node;
    }

    /**
     * @brief Removes a child node from the node.
     * @param name Name of child to remove
     * @return True if child was successfully removed
     */
    bool removeChild(const std::string &name)
    {
      return (m_children.erase(name) == 1);
    }

    /** @} */

    /**
     * @brief Updates this node frm another.
     * @param other Node to update from
     *
     * Existing keys in this node are unmodified.
     *
     * Any child nodes and keys in other that are not in this are added to
     * this.
     *
     * Useful for ensuring a minimum configuration is present without modifying
     * customised settings.
     */
    void updateFromOther(KVNode &other)
    {
      // Update any keys that are in the second node but not this one
      for (auto it = other.keys().begin(); it != other.keys().end(); ++it)
      {
        if (!hasKey(it->first))
          m_keys[it->first] = it->second;
      }

      // For all children of the other node
      for (auto it = other.children().begin(); it != other.children().end(); ++it)
      {
        // If the child also exists in this node then update it
        if (hasChild(it->first))
          m_children[it->first].updateFromOther(it->second);
        // Otherwise add it as a new child
        else
          addChild(it->second);
      }
    }

  private:
    friend class INIKeyValueStore;

    std::string m_name;                        //!< Name of this node
    std::map<std::string, std::string> m_keys; //!< Map of keys under this node
    std::map<std::string, KVNode> m_children;  //!< Map of child nodes
  };
}
}

#endif
