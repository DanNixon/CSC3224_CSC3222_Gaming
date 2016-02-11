/** @file */

#pragma once

#include "SceneObject.h"
#include "Mesh.h"
#include "Shader.h"

/**
 * @class RenderableObject
 * @brief Represents a renderable item in a Scene.
 */
class RenderableObject : public SceneObject
{
public:
  static const int NUM_TEXTURES = 2;

  RenderableObject();
  RenderableObject(Mesh *m, Shader *s, GLuint t = 0);
  ~RenderableObject();

  void setMesh(Mesh *m)
  {
    m_mesh = m;
  }

  Mesh *mesh() const
  {
    return m_mesh;
  }

  void setShader(Shader *s)
  {
    m_shader = s;
  }

  Shader *shader() const
  {
    return m_shader;
  }

  void setTexture(int i, GLuint tex)
  {
    m_textures[i] = tex;
  }

  GLuint texture(int i) const
  {
    return m_textures[i];
  }

  //virtual void update(float msec);
  virtual void render();

private:
  Mesh *m_mesh;     //!< Mesh represented by this object
  Shader *m_shader; //!< Shader used to render m_mesh
  GLuint m_textures[NUM_TEXTURES]; //!< Textures used on m_mesh
};
