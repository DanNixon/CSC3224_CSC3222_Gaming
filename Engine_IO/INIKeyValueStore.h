#pragma once

#include "IKeyValueStore.h"

class INIKeyValueStore : public IKeyValueStore
{
public:
  INIKeyValueStore();
  virtual ~INIKeyValueStore();

  bool load(std::istream &stream);
  bool save(std::ostream &stream);

private:
  void parseNode(std::istream &stream, KVNode &node, bool root = false);
  void outputNode(std::ostream &stream, const KVNode &node);
};