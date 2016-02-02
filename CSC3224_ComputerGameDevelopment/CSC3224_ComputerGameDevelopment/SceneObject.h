#pragma once

#include "Matrix4.h"
#include "Mesh.h"
#include "Shader.h"
#include "Scene.h"

class SceneObject
{
public:
  static const int NUM_TEXTURES = 2;

  SceneObject(void);
  SceneObject(Mesh *m, Shader *s, GLuint t = 0);
  ~SceneObject(void);

  Mesh *GetMesh() const
  {
    return mesh;
  }

  void SetMesh(Mesh *m)
  {
    mesh = m;
  }

  Shader *GetShader() const
  {
    return shader;
  }

  void SetShader(Shader *s)
  {
    shader = s;
  }

  GLuint GetTexture(int i) const
  {
    return textures[i];
  }

  void SetTexture(int i, GLuint tex)
  {
    textures[i] = tex;
  }

  void SetModelMatrix(Matrix4 mat)
  {
    modelMatrix = mat;
  }

  Matrix4 GetModelMatrix() const
  {
    return modelMatrix;
  }

  virtual void Update(float msec);

  void AddChild(SceneObject &child)
  {
    children.push_back(&child);
    child.parent = this;
    child.scene = scene;
  }

  Matrix4 GetWorldTransform() const
  {
    return worldTransform;
  }

  const vector<SceneObject *> &GetChildren() const
  {
    return children;
  }

  void render();

protected:
  friend class Scene;

  Mesh *mesh;
  Shader *shader;

  GLuint textures[NUM_TEXTURES];

  Matrix4 modelMatrix;
  Matrix4 worldTransform;

  SceneObject *parent;
  Scene *scene;
  vector<SceneObject *> children;
};
