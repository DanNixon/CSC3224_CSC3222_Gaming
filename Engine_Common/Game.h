/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_COMMON_GAME_H_
#define _ENGINE_COMMON_GAME_H_

#define NOMINMAX

#include <string>
#include <vector>

#include <SDL/SDL.h>
#include <Windows.h>

#include "IEventHandler.h"
#include "MessageQueue.h"

#include <Engine_IO/INIKeyValueStore.h>

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
    float lastFired;        //!< Last time the timer fired (in milliseconds)
    float interval;         //!< Timer interval (in milliseconds)
    float profileStartTime; //!< Time at which loop began (in milliseconds, for
                            //! profiling)
    std::string loopName;   //!< Name of loop
  };

  /**
   * @class Game
   * @author Dan Nixon
   * @brief Contains setup and shutdown logic for the game engine, should be the
   *        base class of any game using the engine.
   */
  class Game : public Engine::IO::INIKeyValueStore
  {
  public:
    /**
     * @var MAX_TIMED_LOOPS
     * @brief Max number of timed loops that can be configured.
     */
    static const int MAX_TIMED_LOOPS = 8;

    Game(const std::string &name, std::pair<int, int> resolution);
    virtual ~Game();

    int run();
    void exit();

    float time() const;

    /**
     * @brief Returns the name of the game.
     * @return Game name
     */
    inline std::string name() const
    {
      return m_name;
    }

    /** @name Window functions
     *  @{
     */

    /**
     * @brief Gets the width of the window.
     * @return Window width
     */
    inline int windowX() const
    {
      return m_windowWidth;
    }

    /**
     * @brief Gets the height of the window.
     * @return Window height
     */
    inline int windowY() const
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
    void removeEventHandler(IEventHandler *handler);

    /**
     * @brief Gets a reference to the message queue.
     * @return Reference to message queue
     */
    inline MessageQueue &messageQueue()
    {
      return m_msgQueue;
    }

    /** @name Configuration functions
     *  @{
     */

    bool loadConfig();
    bool saveConfig();

    /**
     * @brief Checks f this was the first time the game was launched based on
     *        the presence of the configuration file.
     * @return True if the game is being launched for the first time
     */
    inline bool isFirstRun() const
    {
      return m_firstRun;
    }

    /**
     * @brief Gets the game save directory.
     * @return Save directory
     */
    inline std::string gameSaveDirectory() const
    {
      return m_gameDirectory;
    }

    /**
     * @brief Sets configuration auto save on game termination.
     * @param saveOnExit If the game will be saved on exit
     */
    inline void setConfigSaveOnExit(bool saveOnExit)
    {
      m_saveOnExit = saveOnExit;
    }

    /**
     * @brief Checks if the configuration will be saved on game termination.
     * @return True if the game will be saved on exit
     */
    inline bool configSaveOnExit() const
    {
      return m_saveOnExit;
    }

    /**
     * @brief Gets the full path to the configuration file.
     * @return Config file path
     */
    inline std::string configFilePath() const
    {
      return m_gameDirectory + m_configFilename;
    }

    /** @} */

  protected:
    virtual void gameLoadScreen();

    /**
     * @brief Performs any setup specific to the game.
   * @return Result (0 for succesful startup)
     */
    virtual int gameStartup() = 0;

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

    /**
     * @brief Sets the default configuration options.
     * @param node Node to add default options to
     */
    virtual void defaultConfigOptions(Engine::IO::KVNode &node)
    {
    }

  private:
    int init();
    void close();

    SDL_Window *m_window;    //!< SDL window
    SDL_GLContext m_context; //!< GL context

    LARGE_INTEGER m_freq;  //!< Performance counter frequency
    LARGE_INTEGER m_start; //!< Performance timer start time

    std::string m_gameDirectory;  //!< Path to the game save directory
    std::string m_configFilename; //!< Name of the configuration file
    bool m_firstRun;              //!< Flag indicating first run based on missing config file
    bool m_saveOnExit;            //!< Falg indicating if config should be saved on game exit

  protected:
    friend class Profiler;

    const std::string m_name; //!< Name of the game

    const int m_windowWidth;  //!< Window width
    const int m_windowHeight; //!< Window height

    bool m_run; //!< Flag indicating the same loop should be executed

    Profiler *m_profiler; //!< Profiler instance

    IEventHandler::HandlerList m_eventHandlers;      //!< List of event handlers
    GameLoopConfiguration *m_loops[MAX_TIMED_LOOPS]; //!< Configs for timed loops

    MessageQueue m_msgQueue; //!< Message queue used within this game
  };
}
}

#endif
