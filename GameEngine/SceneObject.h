/** @file */

#pragma once

#include "Matrix4.h"
#include "Mesh.h"
#include "Shader.h"
#include "Scene.h"

// TODO: Separate render stuff into a subclass of SceneObject

/**
 * @class SceneObject
 * @brief Represents an item in a Scene.
 */
class SceneObject
{
public:
  /**
   * @typedef SceneObjectIter
   * @brief Const iterator for items of a vector of SceneObject.
   */
  typedef vector<SceneObject *>::const_iterator SceneObjectIter;

  static const int NUM_TEXTURES = 2;

  SceneObject();
  SceneObject(Mesh *m, Shader *s, GLuint t = 0);
  ~SceneObject();

  /**
   * @brief Adds a SceneObject as a child of this object.
   * @param child Child SceneObject
   */
  void addChild(SceneObject &child)
  {
    m_children.push_back(&child);
    child.m_parent = this;
    child.m_scene = m_scene;
  }

  /**
   * @brief Gets the list of children SceneObject of this object.
   * @return List of children
   */
  const vector<SceneObject *> &children() const
  {
    return m_children;
  }

  /**
   * @brief Tests if this object is visually renderable.
   * @return True if this object can be rendered.
   */
  bool isRenderable() const
  {
    return m_mesh && m_shader;
  }

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

  void setModelMatrix(Matrix4 mat)
  {
    m_modelMatrix = mat;
  }

  Matrix4 modelMatrix() const
  {
    return m_modelMatrix;
  }

  Matrix4 worldTransform() const
  {
    return m_worldTransform;
  }

  virtual void update(float msec);
  void render();

private:
  friend class Scene;

  Mesh *m_mesh;     //!< Mesh represented by this object
  Shader *m_shader; //!< Shader used to render m_mesh

  GLuint m_textures[NUM_TEXTURES]; //!< Textures used on m_mesh

  Matrix4 m_modelMatrix;    //!< Local model matrix (relative to parent)
  Matrix4 m_worldTransform; //!< World matrix (relative to world origin)

  SceneObject *m_parent;            //!< Parent SceneObject
  Scene *m_scene;                   //!< Scene this object belongs to
  vector<SceneObject *> m_children; //!< Children
};
