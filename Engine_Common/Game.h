/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <string>
#include <vector>

#include <SDL/SDL.h>

#include "IEventHandler.h"

namespace Engine
{
namespace Common
{
  /**
   * @class Game
   * @author Dan Nxion
   * @brief Contains setup and shutdown logic for the game engine, should be the
   *        base class of any game using the engine.
   */
  class Game
  {
  public:
    Game(std::string WindowTitle, std::pair<int, int> resolution);
    virtual ~Game();

    bool init();
    void run();

    /**
     * @brief Checks to see if the framework is initialised after a call to
     *        init().
     * @return True for a successful initialisation
     * @see Game::init
     */
    bool isInitialised() const
    {
      return m_initialised;
    }

    void addEventHandler(IEventHandler *handler);

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

  protected:
    /**
     * @brief Performs any setup specific to the game.
     */
    virtual void gameStartup() = 0;

    /**
     * @brief The main game loop.
     * @param dtUs Time since last loop in microseconds
     */
    virtual void gameLoop(unsigned long dtUs) = 0;

    /**
     * @brief Performs any shutdown logic specific to the game.
     */
    virtual void gameShutdown() = 0;

  private:
    void close();

    SDL_Window *m_window;    //!< SDL window
    SDL_GLContext m_context; //!< GL context

  protected:
    bool m_initialised;        //!< If the framework is initialised
    std::string m_windowTitle; //!< Window title
    int m_windowWidth;         //!< Window width
    int m_windowHeight;        //!< Window height
    IEventHandler::HandlerList m_eventHandlers; //!< List of event handlers
  };
}
}
