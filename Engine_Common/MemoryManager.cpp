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
  /**
   * @brief Compare the release order of two managed items.
   * @param a First item
   * @param b Second item
   * @return True if a should be deallocated before b
   */
  bool MemoryManager::CompareItems(IMemoryManaged *a, IMemoryManaged *b)
  {
    return a->releaseOrder() < b->releaseOrder();
  }

  /**
   * @brief Records allocation of a managed item.
   * @param item Pointer to item
   */
  void MemoryManager::recordAllocation(IMemoryManaged *item)
  {
    m_allocatedItems.push_back(item);
  }

  /**
   * @brief Releases a specific item.
   * @param item Item to release
   */
  void MemoryManager::release(IMemoryManaged *item)
  {
    auto it = std::find(m_allocatedItems.begin(), m_allocatedItems.end(), item);
    if (it != m_allocatedItems.end())
    {
      delete *it;
      m_allocatedItems.erase(it);
    }
  }

  /**
   * @brief Releases all recorded allocations.
   */
  void MemoryManager::releaseAll()
  {
    std::sort(m_allocatedItems.begin(), m_allocatedItems.end(), MemoryManager::CompareItems);

    for (auto it = m_allocatedItems.begin(); it != m_allocatedItems.end(); ++it)
    {
      delete *it;
    }

    m_allocatedItems.clear();
  }

  /**
   * @brief Returns the number of recorded allocations.
   * @return Number of allocations
   */
  size_t MemoryManager::numAllocations() const
  {
    return m_allocatedItems.size();
  }
}
}
