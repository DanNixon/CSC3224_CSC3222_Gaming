/**
 * @file
 * @author Dan Nixon
 */

#include "ConfigurableGame.h"

namespace Engine
{
namespace Common
{
  /**
   * @copydoc Game::Game
   */
  ConfigurableGame::ConfigurableGame(const std::string &name, std::pair<int, int> resolution)
      : Game(name, resolution)
  {
  }

  ConfigurableGame::~ConfigurableGame()
  {
  }

  /**
   * @brief Loads the game configuration from the config .ini file.
   */
  void ConfigurableGame::loadConfig()
  {
    // TODO
  }

  /**
  * @brief Saves the game configuration to the config .ini file.
  */
  void ConfigurableGame::saveConfig() const
  {
    // TODO
  }

  /**
   * @copydoc Game::gameShutdown
   */
  void ConfigurableGame::gameShutdown()
  {
    if (m_saveOnExit)
      saveConfig();
  }
}
}
