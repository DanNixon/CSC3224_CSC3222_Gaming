#pragma once

#include <string>
#include <map>

class KVNode
{
public:
  KVNode(const std::string &name = "")
      : m_name(name)
  {
  }

  virtual ~KVNode()
  {
    m_keys.clear();
    m_children.clear();
  }

  std::string name() const
  {
    return m_name;
  }

  size_t numKeys() const
  {
    return m_keys.size();
  }

  bool hasKey(const std::string &key) const
  {
    return (m_keys.find(key) != m_keys.end());
  }

  std::string get(const std::string &key)
  {
    return m_keys[key];
  }

  void set(const std::string &key, const std::string &value)
  {
    m_keys[key] = value;
  }

  bool remove(const std::string &key)
  {
    return (m_keys.erase(key) == 1);
  }

  size_t numChildren() const
  {
    return m_children.size();
  }

  bool hasChild(const std::string &name) const
  {
    return (m_children.find(name) != m_children.end());
  }

  KVNode child(const std::string &name)
  {
    return m_children[name];
  }

  void addChild(KVNode node)
  {
    m_children[node.name()] = node;
  }

  bool removeChild(const std::string &name)
  {
    return (m_children.erase(name) == 1);
  }

private:
  friend class INIKeyValueStore;

  std::string m_name;                        //!< Name of this node
  std::map<std::string, std::string> m_keys; //!< Map of keys under this node
  std::map<std::string, KVNode> m_children;  //!< Map of child nodes
};