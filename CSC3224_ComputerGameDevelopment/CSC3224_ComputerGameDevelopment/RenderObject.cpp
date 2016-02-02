#include "RenderObject.h"

RenderObject::RenderObject(void)
{
  for (int i = 0; i < NUM_TEXTURES; i++)
    textures[i] = NULL;

  mesh = NULL;
  shader = NULL;
  parent = NULL;
}

RenderObject::RenderObject(Mesh *m, Shader *s, GLuint t)
{
  for (int i = 0; i < NUM_TEXTURES; i++)
    textures[i] = NULL;

  mesh = m;
  shader = s;
  textures[0] = t;
  parent = NULL;
}

RenderObject::~RenderObject(void)
{
  if (mesh != NULL)
    delete mesh;

  if (shader != NULL)
    delete shader;

  if (parent != NULL)
    delete parent;
}

void RenderObject::Update(float msec)
{
  if (parent)
    worldTransform = parent->modelMatrix * modelMatrix;
  else
    worldTransform = modelMatrix;

  for (vector<RenderObject *>::const_iterator i = children.begin(); i != children.end(); ++i)
    (*i)->Update(msec);
}

void RenderObject::Draw() const
{
  if (mesh)
    mesh->Draw();
}
