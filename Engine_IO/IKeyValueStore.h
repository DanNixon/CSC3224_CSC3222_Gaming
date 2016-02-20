#pragma once

#include <string>
#include <istream>
#include <ostream>

#include "KVNode.h"

class IKeyValueStore
{
public:
  IKeyValueStore()
  {
  }

  virtual ~IKeyValueStore()
  {
  }

  KVNode & root()
  {
    return m_root;
  }

  virtual bool load(std::istream &stream) = 0;

  virtual bool save(std::ostream &stream) = 0;

protected:
  KVNode m_root; //!< Root node
};