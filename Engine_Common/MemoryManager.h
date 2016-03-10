/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_COMMON_MEMORYMANAGER_H_
#define _ENGINE_COMMON_MEMORYMANAGER_H_

#include <vector>

#include "IMemoryManaged.h"

namespace Engine
{
	namespace Common
	{
		class MemoryManager
		{
    public:
      static MemoryManager &Instance()
      {
        static MemoryManager instance;
        return instance;
      }

      static bool CompareItems(IMemoryManaged * a, IMemoryManaged * b);

      void recordAllocation(IMemoryManaged * item);
      void release(IMemoryManaged * item);
      void releaseAll();

      size_t numAllocations() const;

    private:
      std::vector<IMemoryManaged *> m_allocatedItems;

		private:
      MemoryManager() {}
      MemoryManager(const MemoryManager &) {}
      void operator=(const MemoryManager &) {}
		};
	}
}

#endif