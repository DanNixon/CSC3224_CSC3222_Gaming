/** @file */

#pragma once

#include "Matrix4.h"
#include "Mesh.h"
#include "Shader.h"
#include "Scene.h"

class SceneObject
{
public:
  typedef vector<SceneObject *>::const_iterator SceneObjectIter;

  static const int NUM_TEXTURES = 2;

  SceneObject();
  SceneObject(Mesh *m, Shader *s, GLuint t = 0);
  ~SceneObject();

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

  void addChild(SceneObject &child)
  {
    m_children.push_back(&child);
    child.m_parent = this;
    child.m_scene = m_scene;
  }

  Matrix4 worldTransform() const
  {
    return m_worldTransform;
  }

  const vector<SceneObject *> &children() const
  {
    return m_children;
  }

  virtual void update(float msec);
  void render();

private:
  friend class Scene;

  Mesh *m_mesh;
  Shader *m_shader;

  GLuint m_textures[NUM_TEXTURES];

  Matrix4 m_modelMatrix;
  Matrix4 m_worldTransform;

  SceneObject *m_parent;
  Scene *m_scene;
  vector<SceneObject *> m_children;
};
