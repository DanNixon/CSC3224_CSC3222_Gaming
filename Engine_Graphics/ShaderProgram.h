#pragma once

#include "GL/glew.h"

class Shader;

class ShaderProgram
{
public:
  static const size_t NUM_SHADERS = 5;

  ShaderProgram();
  ~ShaderProgram();

  bool addShader(Shader * s);

  bool link();

  GLuint program() const
  {
    return m_program;
  }

  bool valid() const
  {
    return m_valid;
  }

private:
  GLuint m_program;
  Shader * m_shaders[NUM_SHADERS];
  bool m_valid;
};

