/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_IO_INIKEYVALUESTORE_H_
#define _ENGINE_IO_INIKEYVALUESTORE_H_

#include "IKeyValueStore.h"

namespace Engine
{
namespace IO
{
  /**
   * @class INIKeyValueStore
   * @brief Key value store that loads and saves to INI files.
   * @author Dan Nixon
   */
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
}
}

#endif