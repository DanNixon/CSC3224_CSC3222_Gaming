/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <string>
#include <GL/glew.h>
#include <SOIL/SOIL.h>

namespace Engine
{
namespace Graphics
{
  /**
   * @class Texture
   * @brief Encapsulates a GL texture and image loading.
   * @author Dan Nixon
   */
  class Texture
  {
  public:
    Texture(const std::string &name = "tex");
    virtual ~Texture();

    bool load(const std::string &filename);
    bool valid() const;
    void use(GLuint shaderProgram, int idx) const;

    /**
     * @brief Gets the GL texture for use in rendering.
     * @return GL texture
     */
    GLuint texture() const
    {
      return m_texture;
    }

  private:
    std::string m_name; //!< Name of texture
    GLuint m_texture;   //!< GL texture
  };
}
}
