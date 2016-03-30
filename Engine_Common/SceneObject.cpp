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
      , m_active(true)
      , m_modelMatrix(Matrix4())
      , m_worldTransform(Matrix4())
      , m_parent(nullptr)
  {
  }

  SceneObject::~SceneObject()
  {
  }

  /**
   * @brief Sets the active state of this object.
   * @param active Active
   * @param recursionLevels Maximum depth to traverse the tree
   * @param currentLevel Current recursion level (do not set manually)
   */
  void SceneObject::setActive(bool active, size_t recursionLevels, size_t currentLevel)
  {
    m_active = active;

    if (currentLevel < recursionLevels)
    {
      for (auto it = m_children.begin(); it != m_children.end(); ++it)
        (*it)->setActive(active, recursionLevels, currentLevel + 1);
    }
  }

  /**
   * @brief Updates the state of the object.
   * @param msec Elapsed time since last update in milliseconds
   * @param sys The subsystem being updated
   */
  void SceneObject::update(float msec, Subsystem sys)
  {
    if (m_parent)
      m_worldTransform = m_parent->m_worldTransform * m_modelMatrix;
    else
      m_worldTransform = m_modelMatrix;

    for (SceneObjectListIter i = m_children.begin(); i != m_children.end(); ++i)
      (*i)->update(msec, sys);
  }

  /**
   * @brief Finds a child item.
   * @param name Name of the item
   * @return Pointer to the item, nullptr if not found
   */
  SceneObject *SceneObject::findChild(const std::string &name)
  {
    auto it = std::find_if(m_children.begin(), m_children.end(), [name](SceneObject *o) { return o->name() == name; });
    if (it != m_children.end())
      return *it;
    return nullptr;
  }

  /**
   * @brief Adds this object to a Scene (called automatically).
   * @param scene The scene to add the object to
   */
  void SceneObject::addToScene(Scene *scene)
  {
    m_scene = scene;

    for (SceneObjectListIter i = m_children.begin(); i != m_children.end(); ++i)
      (*i)->addToScene(scene);
  }
}
}
