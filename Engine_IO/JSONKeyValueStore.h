/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "IKeyValueStore.h"

namespace Engine
{
namespace IO
{
  /**
   * @class JSONKeyValueStore
   * @brief Key value store that loads from JSON files.
   * @author Dan Nixon
   */
  class JSONKeyValueStore : public IKeyValueStore
  {
  public:
    JSONKeyValueStore();
    virtual ~JSONKeyValueStore();

    bool load(std::istream &stream);
    bool save(std::ostream &stream);
  };
}
}
