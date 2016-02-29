/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_SHADERS_H_
#define _ENGINE_GRAPHICS_SHADERS_H_

#include "Shader.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @class VertexShader
   * @brief Encapsulation for a vertex shader.
   * @author Dan Nixon
   */
  class VertexShader : public Shader
  {
  public:
    /**
     * @brief Creates a new vertex shader.
     * @param filename GLSL source file
     */
    VertexShader(std::string filename)
        : Shader(filename, GL_VERTEX_SHADER)
    {
    }
  };

  /**
   * @class FragmentShader
   * @brief Encapsulation for a fragment shader.
   * @author Dan Nixon
   */
  class FragmentShader : public Shader
  {
  public:
    /**
     * @brief Creates a new fragement shader.
     * @param filename GLSL source file
     */
    FragmentShader(std::string filename)
        : Shader(filename, GL_FRAGMENT_SHADER)
    {
    }
  };

  /**
   * @class GeometryShader
   * @brief Encapsulation for a geometry shader.
   * @author Dan Nixon
   */
  class GeometryShader : public Shader
  {
  public:
    /**
     * @brief Creates a new geometry shader.
     * @param filename GLSL source file
     */
    GeometryShader(std::string filename)
        : Shader(filename, GL_GEOMETRY_SHADER)
    {
    }
  };

  /**
   * @class TesselationControlShader
   * @brief Encapsulation for a tesselation control shader.
   * @author Dan Nixon
   */
  class TesselationControlShader : public Shader
  {
  public:
    /**
     * @brief Creates a new tesselation control shader.
     * @param filename GLSL source file
     */
    TesselationControlShader(std::string filename)
        : Shader(filename, GL_TESS_CONTROL_SHADER)
    {
    }
  };

  /**
   * @class TesselationEvaluationShader
   * @brief Encapsulation for a tesselation evaluation shader.
   * @author Dan Nixon
   */
  class TesselationEvaluationShader : public Shader
  {
  public:
    /**
     * @brief Creates a new tesselation evaluation shader.
     * @param filename GLSL source file
     */
    TesselationEvaluationShader(std::string filename)
        : Shader(filename, GL_TESS_EVALUATION_SHADER)
    {
    }
  };
}
}

#endif