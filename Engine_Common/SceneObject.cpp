/**
 * @file
 * @author Dan Nixon
 */

#include "SceneObject.h"

using namespace Engine::Maths;

namespace Engine
{
namespace Common
{

/**
 * @brief Creates a new, empty scene object.
 */
SceneObject::SceneObject()
    : m_modelMatrix(Matrix4())
    , m_worldTransform(Matrix4())
    , m_parent(NULL)
{
}

SceneObject::~SceneObject()
{
}

/**
 * @brief Updates the state of the object.
 * @param msec Elapsed time since last update in milliseconds
 */
void SceneObject::update(float msec)
{
  if (m_parent)
    m_worldTransform = m_parent->m_modelMatrix * m_modelMatrix;
  else
    m_worldTransform = m_modelMatrix;

  for (SceneObjectIter i = m_children.begin(); i != m_children.end(); ++i)
    (*i)->update(msec);
}

/**
 * @brief Renders renderable objects.
 */
void SceneObject::render()
{
  for (SceneObjectIter i = m_children.begin(); i != m_children.end(); ++i)
    (*i)->render();
}

/**
 * @brief Adds this object to a Scene (called automatically).
 * @param scene The scene to add the object to
 */
void SceneObject::addToScene(Scene *scene)
{
  m_scene = scene;

  for (SceneObjectIter i = m_children.begin(); i != m_children.end(); ++i)
    (*i)->addToScene(scene);
}
}
}
