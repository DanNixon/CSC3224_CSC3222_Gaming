/**
 * @file
 * @author Dan Nixon
 */

#include <bitset>
#include <type_traits>

#ifndef _ENGINE_UTILITY_ENUMCLASSBITSET_H_
#define _ENGINE_UTILITY_ENUMCLASSBITSET_H_

namespace Engine
{
namespace Utility
{
  /**
  * @class EnumClassBitset
  * @brief Facade class for using an enum class with an std::bitset.
  * @author Dan Nixon
  *
  * Based on this answer on SO:
  * http://stackoverflow.com/questions/17350214/using-enum-class-with-stdbitset/17351268#17351268
  */
  template <typename T> class EnumClassBitset
  {
  public:
    EnumClassBitset()
    {
    }

    /**
     * @brief Tests if a bit is set.
     * @param v Enum value
     * @return True if the bit is set
     */
    bool test(T v) const
    {
      return m_bitset.test(getValueOf(v));
    }

    /**
     * @brief Sets the bit corresponding to a given enum value.
     * @param v Enum value
     * @return Bitset
     */
    EnumClassBitset &set(T v)
    {
      m_bitset.set(getValueOf(v));
      return *this;
    }

    /**
     * @brief Resets the bit corresponding to a given enum value.
     * @param v Enum value
     * @return Bitset
     */
    EnumClassBitset &reset(T v)
    {
      m_bitset.reset(getValueOf(v));
      return *this;
    }

    /**
     * @brief Flips the bit corresponding to a given enum value.
     * @param v Enum value
     * @return Bitset
     */
    EnumClassBitset &flip(T v)
    {
      m_bitset.flip(getValueOf(v));
      return *this;
    }

  private:
    std::bitset<static_cast<typename std::underlying_type<T>::type>(T::MAX_VALUE)> m_bitset; //!< Wrapped bitset

    /**
     * @brief Gets the value of a given enum value.
     * @param v Enum value
     * @return Underlying value
     */
    typename std::underlying_type<T>::type getValueOf(T v) const
    {
      return static_cast<typename std::underlying_type<T>::type>(v);
    }
  };
}
}

#endif
