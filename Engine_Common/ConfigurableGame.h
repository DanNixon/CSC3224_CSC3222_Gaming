/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_COMMON_CONFIGURABLEGAME_H_
#define _ENGINE_COMMON_CONFIGURABLEGAME_H_

#include "Game.h"

#include <Engine_IO/INIKeyValueStore.h>

namespace Engine
{
namespace Common
{
  /**
   * @class ConfigurableGame
   * @brief Allows a game to store configuration options in an .ini file in
   *        the users home directory.
   * @author Dan Nixon
   */
  class ConfigurableGame : public Game, public Engine::IO::INIKeyValueStore
  {
  public:
    ConfigurableGame(const std::string &name, std::pair<int, int> resolution);
    virtual ~ConfigurableGame();

    void loadConfig();
    void saveConfig() const;

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

  protected:
    /**
     * @brief Sets the default configuration options.
     */
    virtual void setDefaultConfigOptions()
    {
    }

    virtual void gameShutdown();

  private:
    bool m_firstRun;   //!< Flag indicating first run based on missing config file
    bool m_saveOnExit; //!< Falg indicating if config should be saved on game exit
  };
}
}

#endif
