/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <string>
#include <vector>

#include <SDL/SDL.h>
#include <Windows.h>

#include "IEventHandler.h"

namespace Engine
{
namespace Common
{
  class Profiler;

  /**
   * @struct GameLoopConfiguration
   * @brief Holds configuration and state for loop timers.
   */
  struct GameLoopConfiguration
  {
    float lastFired;     //!< Last time the timer fired (in milliseconds)
    float interval;      //!< Timer interval (in milliseconds)
    float profileStartTime;
    std::string loopName; //!< Name of loop
  };

  /**
   * @class Game
   * @author Dan Nixon
   * @brief Contains setup and shutdown logic for the game engine, should be the
   *        base class of any game using the engine.
   */
  class Game
  {
  public:
    /**
     * @var MAX_TIMED_LOOPS
     * @brief Max number of timed loops that can be configured.
     */
    static const int MAX_TIMED_LOOPS = 8;

    Game(std::string WindowTitle, std::pair<int, int> resolution);
    virtual ~Game();

    int run();

    float time() const;

    /** @name Window functions
     *  @{
     */

    /**
     * @brief Gets the width of the window.
     * @return Window width
     */
    int windowX() const
    {
      return m_windowWidth;
    }

    /**
     * @brief Gets the height of the window.
     * @return Window height
     */
    int windowY() const
    {
      return m_windowHeight;
    }

    float windowAspect() const;

    void swapBuffers();

    /** @} */

    /** @name Timer/loop functions
     *  @{
     */

    Uint8 addTimedLoop(float interval, const std::string &name);
    void removeTimedLoop(Uint8 id);

    /** @} */

    void addEventHandler(IEventHandler *handler);

  protected:
    virtual void gameLoadScreen();

    /**
     * @brief Performs any setup specific to the game.
     */
    virtual void gameStartup() = 0;

    /**
     * @brief Callback for a given loop.
     * @param id Loop ID
     * @param dtMilliSec Time in milliseconds since this loop last executed
     */
    virtual void gameLoop(Uint8 id, float dtMilliSec) = 0;

    /**
     * @brief Performs any shutdown logic specific to the game.
     */
    virtual void gameShutdown() = 0;

    Profiler * m_profiler;

  private:
    int init();
    void close();

    SDL_Window *m_window;    //!< SDL window
    SDL_GLContext m_context; //!< GL context

    LARGE_INTEGER m_freq;
    LARGE_INTEGER m_start;

  protected:
    friend class Profiler;

    std::string m_windowTitle;                  //!< Window title
    int m_windowWidth;                          //!< Window width
    int m_windowHeight;                         //!< Window height
    IEventHandler::HandlerList m_eventHandlers; //!< List of event handlers
    GameLoopConfiguration
        *m_loops[MAX_TIMED_LOOPS]; //!< Configs for timed loops
  };
}
}
