/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_RESOURCEMANAGMENT_RESOURCELOOKUP_H_
#define _ENGINE_RESOURCEMANAGMENT_RESOURCELOOKUP_H_

#include <map>

namespace Engine
{
namespace ResourceManagment
{
  /**
   * @class ResourceLookup
   * @brief Singleton to hold a map of identifier string to object.
   * @author Dan Nixon
   */
  template <typename T> class ResourceLookup
  {
  public:
    /**
     * @brief Gets an instance of the lookup.
     * @return Instance of this type of lookup
     */
    static ResourceLookup<T> &Instance()
    {
      static ResourceLookup<T> instance;
      return instance;
    }

    /**
     * @brief No copy constructor
     */
    ResourceLookup(ResourceLookup const &) = delete;

    /**
     * @brief No move constructor
     */
    ResourceLookup(ResourceLookup &&) = delete;

    /**
     * @brief No assign copy constructor
     */
    ResourceLookup &operator=(ResourceLookup const &) = delete;

    /**
     * @brief No assign move constructor
     */
    ResourceLookup &operator=(ResourceLookup &&) = delete;

    /**
     * @brief Records a new entry in the lookup.
     * @param name String identifier
     * @param item Resource
     */
    void add(const std::string &name, T item)
    {
      m_items[name] = item;
    }

    /**
     * @brief Gets a resource given its identifier.
     * @param String identifier
     * @returns Resource
     */
    T get(const std::string &name)
    {
      return m_items[name];
    }

    /**
     * @brief Gets a reference to a resource given its identifier.
     * @param String identifier
     * @returns Reference to resource
     */
    T &reference(const std::string &name)
    {
      return m_items[name];
    }

  private:
    std::map<std::string, T> m_items; //!< Wrapped map

  private:
    ResourceLookup()
    {
    }
  };
}
}

#endif
