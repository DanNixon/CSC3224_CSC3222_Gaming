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
    class Texture
    {
    public:
      Texture(const std::string &name = "tex");
      virtual ~Texture();

      bool load(const std::string &filename);
      bool valid() const;
      void use(GLuint shaderProgram, int idx) const;

      GLuint texture() const
      {
        return m_texture;
      }

    private:
      std::string m_name;
      GLuint m_texture;
    };
  }
}