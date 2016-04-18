/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_COMMON_RESOURCELOOKUP_H_
#define _ENGINE_COMMON_RESOURCELOOKUP_H_

#include <map>

namespace Engine
{
namespace Common
{
  /**
   * @class ResourceLookup
   * @brief TODO
   * @author Dan Nixon
   */
  template <typename T>
  class ResourceLookup
  {
  public:
    static ResourceLookup<T> &Instance()
    {
      static ResourceLookup<T> instance;
      return instance;
    }

    void add(const std::string &name, T* item)
    {
      m_items[name] = item;
    }

    T* get(const std::string &name)
    {
      return m_items[name];
    }

  private:
    std::map<std::string, T *> m_items;

  private:
    ResourceLookup()
    {
    }

    ResourceLookup(const ResourceLookup &)
    {
    }

    void operator=(const ResourceLookup &)
    {
    }
  };
}
}

#endif
