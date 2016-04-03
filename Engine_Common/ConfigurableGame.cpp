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
  ConfigurableGame::ConfigurableGame(std::string windowTitle, std::pair<int, int> resolution)
      : Game(windowTitle, resolution)
  {
  }

  ConfigurableGame::~ConfigurableGame()
  {
  }
}
}
