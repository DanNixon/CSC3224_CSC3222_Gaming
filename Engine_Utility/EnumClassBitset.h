/**
 * @file
 * @author Dan Nixon
 */

// 

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
    * Based on this answer on SO: http://stackoverflow.com/questions/17350214/using-enum-class-with-stdbitset/17351268#17351268
    */
    template<typename T>
    class EnumClassBitset
    {
    private:
      std::bitset<static_cast<typename std::underlying_type<T>::type>(T::MAX_VALUE)> m_bitset;

      typename std::underlying_type<T>::type get_value(T v) const
      {
        return static_cast<typename std::underlying_type<T>::type>(v);
      }

    public:
      EnumClassBitset()
      {
      }

      bool test(T pos) const
      {
        return m_bitset.test(get_value(pos));
      }

      EnumClassBitset& set(T pos)
      {
        m_bitset.set(get_value(pos));
        return *this;
      }

      EnumClassBitset& reset(T pos)
      {
        m_bitset.reset(get_value(pos));
        return *this;
      }

      EnumClassBitset& flip(T pos)
      {
        m_bitset.flip(get_value(pos));
        return *this;
      }
    };
  }
}

#endif