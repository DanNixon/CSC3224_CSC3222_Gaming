/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UIMENU_VALUEDMENUITEM_H_
#define _ENGINE_UIMENU_VALUEDMENUITEM_H_

#include "MenuItem.h"

namespace Engine
{
  namespace UIMenu
  {
    template <class T> class ValuedMenuItem : public MenuItem
    {
    public:
      ValuedMenuItem()
      {
      }

      virtual ~ValuedMenuItem()
      {
      }

      T value() const
      {
        return m_value;
      }

      void setValue(const T &value)
      {
        m_value = value;
      }

    private:
      T m_value;
    };
  }
}

#endif