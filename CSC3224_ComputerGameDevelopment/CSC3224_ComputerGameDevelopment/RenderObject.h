#pragma once

#include "Matrix4.h"
#include "Mesh.h"
#include "Shader.h"

class RenderObject
{
public:
  static const int NUM_TEXTURES = 2;

  RenderObject(void);
  RenderObject(Mesh *m, Shader *s, GLuint t = 0);
  ~RenderObject(void);

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

  virtual void Draw() const;

  void AddChild(RenderObject &child)
  {
    children.push_back(&child);
    child.parent = this;
  }

  Matrix4 GetWorldTransform() const
  {
    return worldTransform;
  }

  const vector<RenderObject *> &GetChildren() const
  {
    return children;
  }

protected:
  Mesh *mesh;
  Shader *shader;

  GLuint textures[NUM_TEXTURES];

  Matrix4 modelMatrix;
  Matrix4 worldTransform;

  RenderObject *parent;
  vector<RenderObject *> children;
};
