/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_LIGHT_H_
#define _ENGINE_GRAPHICS_LIGHT_H_

#include <Engine_Common/SceneObject.h>

#include "ShaderProgram.h"

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
    Light(const std::string &name, float radius);
    virtual ~Light();

    /**
     * @brief Gets the radius of the light sphere.
     * @return Radius
     */
    inline float radius() const
    {
      return m_radius;
    }

    /**
     * @brief Sets the radius of the light sphere.
     * @param radius Radius
     */
    inline void setRadius(float radius)
    {
      m_radius = radius;
    }

    /**
     * @brief Gets the intensity of the light.
     * @return Intensity
     */
    inline float intensity() const
    {
      return m_intensity;
    }

    /**
     * @brief Sets the intensity of the light.
     * @param intensity Intensity
     */
    inline void setIntensity(float intensity)
    {
      m_intensity = intensity;
    }

    void use(GLuint program);

  protected:
    std::string m_shaderVarNamePosition;  //!< Name of the shader variable for light position
    std::string m_shaderVarNameRadius;    //!< Name of the shader variable for light radius
    std::string m_shaderVarNameIntensity; //!< Name of the shader variable for light intensity

    float m_radius;    //!< Radius of the light sphere
    float m_intensity; //!< Intensity of the light
  };
}
}

#endif
