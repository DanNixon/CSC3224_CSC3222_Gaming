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
  /**
   * @class IEventHandler
   * @brief Interface for event handlers.
   * @author Dan Nixon
   */
  class IEventHandler
  {
  public:
    /**
     * @typedef HandlerList
     * @brief A list of event handlers.
     */
    typedef std::vector<IEventHandler*> HandlerList;

    /**
     * @typedef HandlerListIter
     * @brief Iterator over a list of event handlers.
     */
    typedef HandlerList::iterator HandlerListIter;

    /**
     * @brief Creates a new event handler that is enabled by default.
     */
    IEventHandler() :
      m_enabled(true)
    {
    }

    virtual ~IEventHandler()
    {
    }

    /**
     * @brief Returns true if this hander is enabled and will process new
     *        events.
     * @return True if enabled.
     * @see IEventHandler::enable
     * @see IEventHandler::disable
     */
    bool enabled() const
    {
      return m_enabled;
    }

    /**
     * @brief Enables this event handler.
     * @see IEventHandler::enabled
     * @see IEventHandler::disable
     */
    void enable()
    {
      m_enabled = true;
    }

    /**
     * @brief Disables this event handler.
     * @see IEventHandler::enabled
     * @see IEventHandler::enable
     */
    void disable()
    {
      m_enabled = false;
    }

    /**
     * @brief Handle an event.
     * @param e Event to handle
     *
     * Implementations must check that m_enabled is true and that the event of
     * of the correct type.
     */
    virtual void handleEvent(const SDL_Event &e) = 0;

  protected:
    bool m_enabled; //!< If this hander is enabled
  };
}
}
