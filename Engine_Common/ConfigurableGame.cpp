/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "ConfigurableGame.h"

#include <Shlobj.h>
#include <fstream>

#include <Engine_IO/DiskUtils.h>
#include <Engine_Logging/Logger.h>
#include <Engine_Utility/StringUtils.h>

using namespace Engine::Utility;
using namespace Engine::IO;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

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
      g_log.error("Failed to get config file location");
    }

    // Create the game directory if it does not exist
    if (!DiskUtils::Exists(m_gameDirectory))
    {
      m_firstRun = true;
      if (!DiskUtils::MakeDirectories(m_gameDirectory))
        g_log.error("Failed to create game save directory");
    }
  }

  ConfigurableGame::~ConfigurableGame()
  {
  }

  /**
   * @brief Loads the game configuration from the config .ini file.
   */
  bool ConfigurableGame::loadConfig()
  {
    // Open file
    std::ifstream file;
    file.open(configFilePath());

    // Check if the file is open
    if ((file.rdstate() & std::ifstream::failbit) != 0)
      return false;

    // Load data
    load(file);

    // Close file
    file.close();

    return true;
  }

  /**
   * @brief Saves the game configuration to the config .ini file.
   */
  bool ConfigurableGame::saveConfig()
  {
    // Open file
    std::ofstream file;
    file.open(configFilePath());

    // Check if the file is open
    if ((file.rdstate() & std::ofstream::failbit) != 0)
      return false;

    // Save data
    save(file);

    // Close file
    file.close();

    return true;
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
    }
    else
    {
      // Load the existing configuration
      m_firstRun = false;
      loadConfig();
    }

    // Update the default configurations
    KVNode defaultRoot;
    defaultConfigOptions(defaultRoot);
    m_root.updateFromOther(defaultRoot);
    saveConfig();

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
