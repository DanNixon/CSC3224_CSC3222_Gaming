/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "Shader.h"

/**
 * @class VertexShader
 * @brief Encapsulation for a vertex shader.
 * @author Dan Nixon
 */
class VertexShader : public Shader
{
public:
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
  TesselationEvaluationShader(std::string filename)
      : Shader(filename, GL_TESS_EVALUATION_SHADER)
  {
  }
};
