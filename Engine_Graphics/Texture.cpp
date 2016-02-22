/**
* @file
* @author Dan Nixon
*/

#include "Texture.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new texture with a given name.
   * @param name Texture name (defaults to "tex")
   *
   * Texture name is used as the uniform name for use in shaders.
   */
  Texture::Texture(const std::string &name)
      : m_name(name)
  {
  }

  Texture::~Texture()
  {
  }

  /**
   * @brief Loads an image file into a GL texture.
   * @param filename Image file to load
   * @return GL texture, 0 if loading failed
   */
  bool Texture::load(const std::string &filename)
  {
    m_texture = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,
                                      SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    return (m_texture != 0);
  }

  /**
   * @brief Checks to see if a valid image has been loaded into the texture.
   * @return True if tecture holds a valid image
   */
  bool Texture::valid() const
  {
    return (m_texture > 0);
  }

  /**
   * @brief Use the texture in rendering.
   * @param shaderProgram Shader program used in rendering
   * @param idx Index of this testure in rendering
   */
  void Texture::use(GLuint shaderProgram, int idx) const
  {
    if (m_texture == 0)
      return;

    glUniform1i(glGetUniformLocation(shaderProgram, m_name.c_str()), idx);
    glActiveTexture(GL_TEXTURE0 + idx);
    glBindTexture(GL_TEXTURE_2D, m_texture);
  }
}
}
