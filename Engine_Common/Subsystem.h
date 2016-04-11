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
   * @brief ENumeration of each subsystem.
   * @author Dan Nixon
   */
  enum class Subsystem
  {
    NONE,

    GRAPHICS,
    PHYSICS,
    AUDIO,
    INPUT,
    AI,

    AUX1,
    AUX2
  };
}
}

#endif
