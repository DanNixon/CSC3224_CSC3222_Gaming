/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Light.h"

#include <Engine_Common/Subsystem.h>
#include <Engine_Maths/Matrix3.h>

using namespace Engine::Common;
using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new light
   * @param name Name of light
   */
  Light::Light(const std::string &name)
      : SceneObject(name)
  {
  }

  Light::~Light()
  {
  }

  /**
   * @copydoc SceneObject::update()
   */
  void Light::update(float msec, Subsystem sys)
  {
    SceneObject::update(msec, sys);

    if (sys == Subsystem::GRAPHICS && m_active)
    {
      // TODO
    }
  }
}
}
