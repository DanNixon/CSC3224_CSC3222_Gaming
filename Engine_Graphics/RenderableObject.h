/** @file */

#pragma once

#include "SceneObject.h"
#include "Mesh.h"
#include "ShaderProgram.h"

/**
 * @class RenderableObject
 * @brief Represents a renderable item in a Scene.
 */
class RenderableObject : public SceneObject
{
public:
  static const int NUM_TEXTURES = 2;

  RenderableObject();
  RenderableObject(Mesh *m, ShaderProgram *s, GLuint t = 0);
  ~RenderableObject();

  /**
   * @brief Sets the Mesh this object renders.
   * @param m Mesh
   * @see RenderableObject::mesh
   */
  void setMesh(Mesh *m)
  {
    m_mesh = m;
  }

  /**
   * @brief Gets the Mesh this object renders.
   * @return Mesh
   * @see RenderableObject::setMesh
   */
  Mesh *mesh() const
  {
    return m_mesh;
  }

  /**
   * @brief Sets the ShaderProgram this object uses to render.
   * @param s Shader program
   * @see RenderableObject::shader
   */
  void setShader(ShaderProgram *s)
  {
    m_shaderProgram = s;
  }

  /**
   * @brief Gets the ShaderProgram this object uses to render.
   * @return Shader program
   * @see RenderableObject::setShader
   */
  ShaderProgram *shader() const
  {
    return m_shaderProgram;
  }

  /**
   * @brief Sets a texture associated with this object.
   * @param i Texture index
   * @param tex Texture
   * @see RenderableObject::texture
   */
  void setTexture(int i, GLuint tex)
  {
    m_textures[i] = tex;
  }

  /**
   * @brief Gets a texture associated with this object.
   * @param i Texture index
   * @return Texture
   * @see RenderableObject::setTexture
   */
  GLuint texture(int i) const
  {
    return m_textures[i];
  }

  virtual void render();

private:
  Mesh *m_mesh;                    //!< Mesh represented by this object
  ShaderProgram *m_shaderProgram;  //!< Shader used to render m_mesh
  GLuint m_textures[NUM_TEXTURES]; //!< Textures used on m_mesh
};
