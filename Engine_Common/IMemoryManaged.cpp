/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
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