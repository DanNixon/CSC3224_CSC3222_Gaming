/** @file */

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "GL/glew.h"

/**
 * @enum ShaderStage
 * @brief Represents a specific shader in the pipeline.
 */
enum ShaderStage
{
  SHADER_VERTEX = 0,
  SHADER_FRAGMENT,
  SHADER_GEOMETRY,
  SHADER_TCS,
  SHADER_TES,
  SHADER_MAX
};

using namespace std;

/**
 * @class Shader
 * @brief Encapsulation for OpenGL shaders.
 * @author Rich Davison, Dan Nixon
 *
 * Modified from the original nclgl library.
 */
class Shader
{
public:
  Shader(string vertex, string fragment, string geometry = "", string tcs = "",
         string tes = "");
  ~Shader();

  /**
   * @brief Returns the shader program.
   * @return Shader program
   */
  GLuint program() const
  {
    return m_program;
  }

  /**
   * @brief Checks if all shaders have been loaded and linked successfully.
   * @return True if shaders are valid
   */
  bool valid() const
  {
    return m_linkSuccess;
  }

private:
  bool loadFile(string filename, string &into);
  GLuint compile(string filename, GLenum type);
  bool link();
  void setDefaultAttributes();

  GLuint m_objects[SHADER_MAX];
  GLuint m_program;

  bool m_loadSuccess;
  bool m_linkSuccess;
};
