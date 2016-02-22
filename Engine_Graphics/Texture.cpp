/**
* @file
* @author Dan Nixon
*/

#include "Texture.h"

namespace Engine
{
namespace Graphics
{
  Texture::Texture(const std::string &name)
      : m_name(name)
  {
  }

  Texture::~Texture()
  {
  }

  bool Texture::load(const std::string &filename)
  {
    m_texture = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,
                                      SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    return (m_texture != 0);
  }

  bool Texture::valid() const
  {
    return (m_texture > 0);
  }

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