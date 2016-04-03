/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_COMMON_CONFIGURABLEGAME_H_
#define _ENGINE_COMMON_CONFIGURABLEGAME_H_

#include <Game.h>

#include <Engine_IO/INIKeyValueStore.h>

namespace Engine
{
namespace Common
{
  /**
   * @class ConfigurableGame
   * @author Dan Nixon
   */
  class ConfigurableGame : public Game, public INIKeyValueStore
  {
  public:
    /**
     * @var MAX_TIMED_LOOPS
     * @brief Max number of timed loops that can be configured.
     */
    static const int MAX_TIMED_LOOPS = 8;

    ConfigurableGame(std::string windowTitle, std::pair<int, int> resolution);
    virtual ~ConfigurableGame();
  };
}
}

#endif
