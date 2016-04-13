/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
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
   *
   * Configuration save on exit is enabled by default.
   */
  class ConfigurableGame : public Game, public Engine::IO::INIKeyValueStore
  {
  public:
    ConfigurableGame(const std::string &name, std::pair<int, int> resolution);
    virtual ~ConfigurableGame();

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

  protected:
    /**
     * @brief Sets the default configuration options.
     */
    virtual void setDefaultConfigOptions()
    {
    }

    virtual int gameStartup();
    virtual void gameShutdown();

  private:
    std::string m_gameDirectory;  //!< Path to the game save directory
    std::string m_configFilename; //!< Name of the configuration file
    bool m_firstRun;              //!< Flag indicating first run based on missing config file
    bool m_saveOnExit;            //!< Falg indicating if config should be saved on game exit
  };
}
}

#endif
