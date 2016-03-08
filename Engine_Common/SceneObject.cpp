/**
 * @file
 * @author Dan Nixon
 */

#include "SceneObject.h"

#include <algorithm>

using namespace Engine::Maths;

namespace Engine
{
namespace Common
{
  /**
   * @brief Creates a new, empty scene object.
   * @param name Name of the object
   */
  SceneObject::SceneObject(const std::string &name)
      : m_name(name)
      , m_modelMatrix(Matrix4())
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
      m_worldTransform = m_parent->m_worldTransform * m_modelMatrix;
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

  SceneObject *SceneObject::findChild(const std::string &name)
  {
    auto it =
        std::find_if(m_children.begin(), m_children.end(),
                     [name](SceneObject *o) { return o->name() == name; });
    if (it != m_children.end())
      return *it;
    return NULL;
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
