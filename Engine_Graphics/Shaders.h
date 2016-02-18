#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
  VertexShader(std::string filename)
      : Shader(filename, GL_VERTEX_SHADER)
  {
  }
};

class FragmentShader : public Shader
{
public:
  FragmentShader(std::string filename)
      : Shader(filename, GL_FRAGMENT_SHADER)
  {
  }
};

class GeometryShader : public Shader
{
public:
  GeometryShader(std::string filename)
      : Shader(filename, GL_GEOMETRY_SHADER)
  {
  }
};

class TesselationControlShader : public Shader
{
public:
  TesselationControlShader(std::string filename)
      : Shader(filename, GL_TESS_CONTROL_SHADER)
  {
  }
};

class TesselationEvaluationShader : public Shader
{
public:
  TesselationEvaluationShader(std::string filename)
      : Shader(filename, GL_TESS_EVALUATION_SHADER)
  {
  }
};