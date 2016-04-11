/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_SHADER_H_
#define _ENGINE_GRAPHICS_SHADER_H_

#include <fstream>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include <Engine_Common/IMemoryManaged.h>

namespace Engine
{
namespace Graphics
{
  /**
   * @class Shader
   * @brief Encapsulation for a single OpenGL shader.
   * @author Dan Nixon
   */
  class Shader : public Engine::Common::IMemoryManaged
  {
  public:
    Shader(std::string filename, GLuint stage);
    virtual ~Shader();

    /**
     * @copydoc IMemoryManaged::releaseOrder
     */
    virtual int releaseOrder() const
    {
      return 6;
    }

    /**
     * @brief Returns the type of shader (shader stage).
     * @return Shader stage
     */
    GLuint stage() const
    {
      return m_stage;
    }

    /**
     * @brief Returns the GL shader object.
     * @return Shader object
     */
    GLuint object() const
    {
      return m_shaderObject;
    }

    /**
     * @brief Checks if the shader has been compiled.
     * @return True if shader is valid
     */
    bool valid() const
    {
      return m_valid;
    }

  private:
    bool loadFile(std::string filename, std::string &into);
    bool compile(std::string filename);

    GLuint m_stage;        //!< Shader stage
    GLuint m_shaderObject; //!< GL shader object

    bool m_valid; //!< Flag indicating validity of shader
  };
}
}

#endif
