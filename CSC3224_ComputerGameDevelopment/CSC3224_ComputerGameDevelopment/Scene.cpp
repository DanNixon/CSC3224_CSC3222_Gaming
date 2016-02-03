#include "Scene.h"

#include "SceneObject.h"

Scene::Scene(SceneObject *root, Matrix4 view, Matrix4 projection)
    : m_root(root)
    , m_projectionMatrix(view)
    , m_viewMatrix(projection)
{
  root->m_scene = this;
}

Scene::~Scene()
{
}

void Scene::setViewMatrix(Matrix4 view)
{
  m_viewMatrix = view;
}

Matrix4 Scene::viewMatrix()
{
  return m_viewMatrix;
}

void Scene::setProjectionMatrix(Matrix4 projection)
{
  m_projectionMatrix = projection;
}

Matrix4 Scene::projectionMatrix()
{
  return m_projectionMatrix;
}

void Scene::update()
{
  m_root->update(0);
}

void Scene::render()
{
  m_root->render();
}
