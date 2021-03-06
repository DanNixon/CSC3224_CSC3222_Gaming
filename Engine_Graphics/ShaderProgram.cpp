/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "ShaderProgram.h"

#include <Engine_Logging/Logger.h>

#include "Mesh.h"
#include "Shader.h"

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new, empty shader program.
   */
  ShaderProgram::ShaderProgram()
      : m_valid(false)
  {
    for (size_t i = 0; i < NUM_SHADERS; i++)
      m_shaders[i] = nullptr;

    m_program = glCreateProgram();
  }

  /**
   * @brief Destroys the shader program, deteching all shaders and deleting the
   *        program.
   */
  ShaderProgram::~ShaderProgram()
  {
    for (size_t i = 0; i < NUM_SHADERS; i++)
    {
      if (m_shaders[i] != nullptr)
        glDetachShader(m_program, m_shaders[i]->object());
    }

    glDeleteProgram(m_program);
  }

  /**
   * @brief Adds a Shader to the program.
   * @param s Shader to add
   * @return True if the shader was added
   */
  bool ShaderProgram::addShader(Shader *s)
  {
    for (size_t i = 0; i < NUM_SHADERS; i++)
    {
      if (m_shaders[i] == nullptr)
      {
        m_shaders[i] = s;
        return true;
      }
    }

    return false;
  }

  /**
   * @brief Links the shader program.
   * @return True if the program was successfully linked
   */
  bool ShaderProgram::link()
  {
    if (m_valid)
    {
      g_log.error("Not all shaders are compiled, cannot link shader program");
      return false;
    }

    glBindAttribLocation(m_program, VERTEX_BUFFER, "position");
    glBindAttribLocation(m_program, COLOUR_BUFFER, "colour");
    glBindAttribLocation(m_program, NORMAL_BUFFER, "normal");
    glBindAttribLocation(m_program, TANGENT_BUFFER, "tangent");
    glBindAttribLocation(m_program, TEXTURE_BUFFER, "texCoord");

    for (size_t i = 0; i < NUM_SHADERS; i++)
    {
      if (m_shaders[i] != nullptr)
      {
        if (!m_shaders[i]->valid())
          return false;

        glAttachShader(m_program, m_shaders[i]->object());
      }
    }

    glLinkProgram(m_program);

    GLint status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
      char error[2048];
      glGetProgramInfoLog(m_program, sizeof(error), nullptr, error);
      g_log.error("Linking failed! Error log: " + std::string(error));
      return false;
    }

    m_valid = (status != GL_FALSE);

    if (!m_valid)
    {
      char errorMsg[2048];
      glGetInfoLogARB(m_program, sizeof(errorMsg), nullptr, errorMsg);
      g_log.error("Shader program failed to link: " + std::string(errorMsg));
    }

    return m_valid;
  }
}
}
