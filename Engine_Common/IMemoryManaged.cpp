/**
 * @file
 * @author Dan Nixon
 */

#include "IMemoryManaged.h"

#include "MemoryManager.h"

namespace Engine
{
  namespace Common
  {
    IMemoryManaged::IMemoryManaged()
    {
      MemoryManager::Instance().recordAllocation(this);
    }

    IMemoryManaged::~IMemoryManaged()
    {
    }
  }
}