/**
 * @file
 * @author Dan Nixon
 */

#include "MemoryManager.h"

#include <algorithm>

#include <iostream>

namespace Engine
{
  namespace Common
  {
    bool MemoryManager::CompareItems(IMemoryManaged * a, IMemoryManaged * b)
    {
      return a->releasePriority() < b->releasePriority();
    }

    void MemoryManager::recordAllocation(IMemoryManaged * item)
    {
      m_allocatedItems.push_back(item);
    }

    void MemoryManager::release(IMemoryManaged * item)
    {
      auto it = std::find(m_allocatedItems.begin(), m_allocatedItems.end(), item);
      if (it != m_allocatedItems.end())
      {
        delete *it;
        m_allocatedItems.erase(it);
      }
    }

    void MemoryManager::releaseAll()
    {
      std::sort(m_allocatedItems.begin(), m_allocatedItems.end(), MemoryManager::CompareItems);

      for (auto it = m_allocatedItems.begin(); it != m_allocatedItems.end(); ++it)
      {
        std::cout << (*it)->releasePriority() << std::endl;
        delete *it;
      }

      m_allocatedItems.clear();
    }

    size_t MemoryManager::numAllocations() const
    {
      return m_allocatedItems.size();
    }
  }
}