#include "IKeyValueStore.h"

IKeyValueStore::IKeyValueStore()
{
}

IKeyValueStore::~IKeyValueStore()
{
}

std::string IKeyValueStore::getValue(const std::string &fullKey) const
{
  if (m_root == NULL)
    return std::string();

  // TODO
}