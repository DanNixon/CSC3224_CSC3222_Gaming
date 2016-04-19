/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_LIGHT_H_
#define _ENGINE_GRAPHICS_LIGHT_H_

#include <Engine_Common/SceneObject.h>

namespace Engine
{
namespace Graphics
{
  /**
   * @class Light
   * @brief Represents a light source in a Scene.
   * @author Dan Nixon
   */
  class Light : public Engine::Common::SceneObject
  {
  public:
    Light(const std::string &name);
    ~Light();

    virtual void update(float msec, Engine::Common::Subsystem sys);
  };
}
}

#endif
