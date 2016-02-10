/** @file */

#include "SceneObject.h"

SceneObject::SceneObject()
    : m_modelMatrix(Matrix4())
    , m_worldTransform(Matrix4())
    , m_parent(NULL)
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::update(float msec)
{
  if (m_parent)
    m_worldTransform = m_parent->m_modelMatrix * m_modelMatrix;
  else
    m_worldTransform = m_modelMatrix;

  for (SceneObjectIter i = m_children.begin(); i != m_children.end(); ++i)
    (*i)->update(msec);
}

void SceneObject::render()
{
  for (SceneObjectIter i = m_children.begin(); i != m_children.end(); ++i)
    (*i)->render();
}

void SceneObject::addToScene(Scene * scene)
{
  m_scene = scene;

  for (SceneObjectIter i = m_children.begin(); i != m_children.end(); ++i)
    (*i)->addToScene(scene);
}