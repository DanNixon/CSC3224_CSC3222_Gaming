/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_COMMON_IMEMORYMANAGED_H_
#define _ENGINE_COMMON_IMEMORYMANAGED_H_

namespace Engine
{
namespace Common
{
  class IMemoryManaged
  {
  public:
    IMemoryManaged();
    virtual ~IMemoryManaged();

    virtual int releasePriority() const
    {
      return 0;
    }
  };
}
}

#endif