#pragma once

#include <string>

class KVNode;

class IKeyValueStore
{
public:
  IKeyValueStore();
  virtual ~IKeyValueStore();

  std::string getValue(const std::string &fullKey) const;

  virtual void load(const std::string &filename) = 0;

  virtual void save(const std::string &filename) = 0;

private:
  KVNode * m_root; //!< Root node
};