/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <map>
#include <string>

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
     * @brief Gets the value of a key.
     * @param key Key to retrieve
     * @return Value
     */
    std::string get(const std::string &key)
    {
      return m_keys[key];
    }

    /**
     * @brief Sets the value of a key.
     * @param key Key to set
     * @param value Value
     */
    void set(const std::string &key, const std::string &value)
    {
      m_keys[key] = value;
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

    /**
     * @brief Gets a child node with a given name.
     * @param name Name of child not to retrieve
     * @return Child node
     */
    KVNode child(const std::string &name)
    {
      return m_children[name];
    }

    /**
     * @brief Adds a child node to this node..
     * @param node Child node to add
     */
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

  private:
    friend class INIKeyValueStore;

    std::string m_name;                        //!< Name of this node
    std::map<std::string, std::string> m_keys; //!< Map of keys under this node
    std::map<std::string, KVNode> m_children;  //!< Map of child nodes
  };
}
}
