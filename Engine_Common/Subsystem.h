/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_COMMON_SUBSYSTEM_H_
#define _ENGINE_COMMON_SUBSYSTEM_H_

namespace Engine
{
namespace Common
{
  /**
   * @brief Enumeration of each subsystem.
   * @author Dan Nixon
   */
  enum class Subsystem
  {
    NONE,
    ALL,

    GRAPHICS,
    PHYSICS,
    AUDIO,
    INPUT,
    AI,
    UI_HUD,
    UI_MENU,

    GAME_LOGIC,

    USER1,
    USER2,
    USER3,
    USER4,
    USER5
  };
}
}

#endif
