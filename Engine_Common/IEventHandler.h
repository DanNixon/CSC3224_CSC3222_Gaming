/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <vector>
#include <initializer_list>

#include <SDL.h>

namespace Engine
{
namespace Common
{
  class IEventHandler
  {
  public:
    typedef std::vector<IEventHandler*> HandlerList;
    typedef HandlerList::iterator HandlerListIter;

    IEventHandler() :
      m_enabled(true)
    {
    }

    virtual ~IEventHandler()
    {
    }

    bool enabled() const
    {
      return m_enabled;
    }

    bool enable()
    {
      m_enabled = true;
    }

    bool disable()
    {
      m_enabled = false;
    }

    virtual void handleEvent(const SDL_Event &e) = 0;

  protected:
    bool m_enabled;
  };
}
}