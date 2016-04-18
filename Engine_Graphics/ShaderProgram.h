/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_SHADERPROGRAM_H_
#define _ENGINE_GRAPHICS_SHADERPROGRAM_H_

#include <GL/glew.h>

#include <Engine_ResourceManagment/IMemoryManaged.h>
#include <Engine_ResourceManagment/ResourceLookup.h>

namespace Engine
{
namespace Graphics
{
  class Shader;

  /**
   * @class ShaderProgram
   * @brief Encapsulation for a GL shader program.
   * @author Dan Nixon
   */
  class ShaderProgram : public Engine::ResourceManagment::IMemoryManaged
  {
  public:
    /**
     * @var NUM_SHADERS
     * @brief Maximum number of shaders in a program.
     */
    static const size_t NUM_SHADERS = 5;

    ShaderProgram();
    ~ShaderProgram();

    /**
     * @copydoc IMemoryManaged::releaseOrder
     */
    virtual int releaseOrder() const
    {
      return 5;
    }

    bool addShader(Shader *s);

    bool link();

    /**
     * @brief Gets the GL program.
     * @return GL shader program
     */
    GLuint program() const
    {
      return m_program;
    }

    /**
     * @brief Tests if the shader program is valid.
     * @return True if valid
     *
     * A program is valid when all shaders are loaded and compiled and the
     * program is linked.
     */
    bool valid() const
    {
      return m_valid;
    }

  private:
    GLuint m_program;               //!< GL shader program
    Shader *m_shaders[NUM_SHADERS]; //!< Array of Shaders in program
    bool m_valid;                   //!< Flag indicating validity of program
  };

  typedef Engine::ResourceManagment::ResourceLookup<ShaderProgram *> ShaderProgramLookup;
}
}

#endif
