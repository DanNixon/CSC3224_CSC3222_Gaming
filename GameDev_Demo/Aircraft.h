/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _GAMEDEV_DEMO_AIRCRAFT_H_
#define _GAMEDEV_DEMO_AIRCRAFT_H_

#include <Engine_Common/SceneObject.h>

namespace GameDev
{
namespace Demo
{
  /**
   * @class Aircraft
   * @brief TODO
   * @author Dan Nixon
   */
  class Aircraft : public Engine::Common::SceneObject
  {
  public:
    Aircraft(const std::string &name);
    virtual ~Aircraft();
  };
}
}

#endif