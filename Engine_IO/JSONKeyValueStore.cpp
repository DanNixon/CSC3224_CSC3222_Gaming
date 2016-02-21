/**
 * @file
 * @author Dan Nixon
 */

#include "JSONKeyValueStore.h"

#include "KVNode.h"

namespace Engine
{
namespace IO
{
  JSONKeyValueStore::JSONKeyValueStore()
  {
  }

  JSONKeyValueStore::~JSONKeyValueStore()
  {
  }

  /**
   * @copydoc IKeyValueStore::load
   */
  bool JSONKeyValueStore::load(std::istream &stream)
  {
    // TODO

    return false;
  }

  /**
   * @copydoc IKeyValueStore::save
   *
   * Saving JSON files is not supported.
   */
  bool JSONKeyValueStore::save(std::ostream &stream)
  {
    return false;
  }
}
}
