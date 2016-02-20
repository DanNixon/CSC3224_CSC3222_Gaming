#pragma once

#include <string>
#include <map>

class KVNode
{
public:
  KVNode(const std::string &name)
    : m_name(name)
  {
  }

  virtual ~KVNode();

  std::string name() const
  {
    return m_name;
  }

  std::string get(const std::string &key) const
  {
    return m_keys[key];
  }

  void set(const std::string &key, const std::string &value)
  {
    m_keys[key] = value;
  }

private:
  std::string m_name; //!< Name of this node
  std::map<std::string, std::string> m_keys; //!< Map of keys under this node
  std::map<std::string, KVNode> m_children; //!< Map of child nodes
};