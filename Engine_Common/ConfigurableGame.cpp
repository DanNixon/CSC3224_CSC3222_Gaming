/**
 * @file
 * @author Dan Nixon
 */

#include "ConfigurableGame.h"

#include <Shlobj.h>
#include <fstream>
#include <iostream>

#include <Engine_IO/DiskUtils.h>
#include <Engine_Utility/StringUtils.h>

using namespace Engine::Utility;
using namespace Engine::IO;

namespace Engine
{
namespace Common
{
  /**
   * @copydoc Game::Game
   */
  ConfigurableGame::ConfigurableGame(const std::string &name, std::pair<int, int> resolution)
      : Game(name, resolution)
      , m_firstRun(false)
      , m_saveOnExit(true)
  {
    // Set the config file name
    WCHAR path[MAX_PATH];
    char charPath[MAX_PATH];
    char c = ' ';
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path)) &&
        SUCCEEDED(WideCharToMultiByte(CP_ACP, 0, path, -1, charPath, 260, &c, NULL)))
    {
      std::string sanitizedName = StringUtils::SanitizeFilename(m_name);
      m_gameDirectory = std::string(charPath) + "\\." + sanitizedName + "\\";
      m_configFilename = sanitizedName + ".ini";
    }
    else
    {
      std::cerr << "Failed to get config file location" << std::endl;
    }

    // Create the game directory if it does not exist
    if (!DiskUtils::Exists(m_gameDirectory))
    {
      m_firstRun = true;
      if (!DiskUtils::MakeDirectories(m_gameDirectory))
        std::cerr << "Failed to create game save directory" << std::endl;
    }
  }

  ConfigurableGame::~ConfigurableGame()
  {
  }

  /**
   * @brief Loads the game configuration from the config .ini file.
   */
  void ConfigurableGame::loadConfig()
  {
    std::ifstream file;
    file.open(configFilePath());
    load(file);
    file.close();
  }

  /**
  * @brief Saves the game configuration to the config .ini file.
  */
  void ConfigurableGame::saveConfig()
  {
    std::ofstream file;
    file.open(configFilePath());
    save(file);
    file.close();
  }

  /**
   * @copydoc Game::gameStartup
   */
  int ConfigurableGame::gameStartup()
  {
    if (!DiskUtils::Exists(configFilePath()))
    {
      // Create the configuration file (with default options) if it does not exist
      m_firstRun = true;
      setDefaultConfigOptions();
      saveConfig();
    }
    else
    {
      // Load the existing configuration
      m_firstRun = false;
      loadConfig();
    }

    return 0;
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
