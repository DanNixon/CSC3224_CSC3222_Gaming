/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_RESOURCEMANAGMENT_IMEMORYMANAGED_H_
#define _ENGINE_RESOURCEMANAGMENT_IMEMORYMANAGED_H_

namespace Engine
{
namespace ResourceManagment
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
     * @return Order
     *
     * Higher order items are released later.
     */
    virtual int releaseOrder() const
    {
      return 0;
    }
  };
}
}

#endif
