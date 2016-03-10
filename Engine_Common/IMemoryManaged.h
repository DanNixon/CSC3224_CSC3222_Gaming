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
  /**
   * @class IMemoryManaged
   * @brief Abstract class for classes that are deallocated at game exit.
   * @author Dan Nixon
   */
  class IMemoryManaged
  {
  public:
    IMemoryManaged();
    virtual ~IMemoryManaged();

    /**
     * @brief Determines the order in which deallocation occurs.
     * @return Priority
     *
     * Higher priorities are released later.
     */
    virtual int releasePriority() const
    {
      return 0;
    }
  };
}
}

#endif
