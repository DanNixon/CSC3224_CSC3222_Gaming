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
   * @param radius Radius of the light
   */
  Light::Light(const std::string &name, float radius)
      : SceneObject(name)
      , m_radius(radius)
      , m_intensity(1.0f)
  {
    m_shaderVarNamePosition = "light_" + name + "_position";
    m_shaderVarNameRadius = "light_" + name + "_radius";
    m_shaderVarNameIntensity = "light_" + name + "_intensity";
  }

  Light::~Light()
  {
  }

  /**
   * @brief Use the light in a shader.
   * @param program Shader program light is to be used in
   *
   * Shader is expected to have already been made active.
   */
  void Light::use(GLuint program)
  {
    Vector3 position = m_worldTransform.positionVector();
    glUniform3fv(glGetUniformLocation(program, m_shaderVarNamePosition.c_str()), 1, (float *)&position);
    glUniform1f(glGetUniformLocation(program, m_shaderVarNameRadius.c_str()), m_radius);
    glUniform1f(glGetUniformLocation(program, m_shaderVarNameIntensity.c_str()), m_intensity);
  }
}
}
