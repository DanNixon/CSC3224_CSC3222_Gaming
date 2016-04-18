/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_COMMON_MEMORYMANAGER_H_
#define _ENGINE_COMMON_MEMORYMANAGER_H_

#include <vector>

#include "IMemoryManaged.h"

namespace Engine
{
namespace Common
{
  /**
   * @class MemoryManager
   * @brief Manager for deallocating memory on game exit.
   * @author Dan Nixon
   */
  class MemoryManager
  {
  public:
    /**
     * @brief Gets the instance of the manager.
     * @return Manager instance
     */
    static MemoryManager &Instance()
    {
      static MemoryManager instance;
      return instance;
    }

    static bool CompareItems(IMemoryManaged *a, IMemoryManaged *b);

    void recordAllocation(IMemoryManaged *item);
    void release(IMemoryManaged *item);
    void releaseAll();

    size_t numAllocations() const;

  private:
    std::vector<IMemoryManaged *> m_allocatedItems; //!< Pointer to all allocated items

  private:
    MemoryManager()
    {
    }

    MemoryManager(const MemoryManager &)
    {
    }

    void operator=(const MemoryManager &)
    {
    }
  };
}
}

#endif
