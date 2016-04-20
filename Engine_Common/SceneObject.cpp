/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "SceneObject.h"

#include <algorithm>
#include <string>

using namespace Engine::Maths;

namespace Engine
{
namespace Common
{
  /**
   * @brief Creates a new, empty scene object.
   * @param name Name of the object
   * @param parent Parent object
   */
  SceneObject::SceneObject(const std::string &name, SceneObject *parent)
      : m_name(name)
      , m_active(true)
      , m_modelMatrix(Matrix4())
      , m_worldTransform(Matrix4())
      , m_parent(nullptr)
  {
    if (parent != nullptr)
      parent->addChild(this);
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
   * @brief Finds an item in the scene tree.
   * @param name Name of the item
   * @param maxDepth Maximum recrusion depth
   * @param level Current level (do not set manually)
   * @return Pointer to the item, nullptr if not found
   */
  SceneObject *SceneObject::find(const std::string &name, size_t maxDepth, size_t level)
  {
    // Check if this is the object
    if (m_name == name)
      return this;

    SceneObject *retVal = nullptr;

    // Search children
    if (level < maxDepth)
    {
      for (SceneObjectListIter it = m_children.begin(); it != m_children.end(); ++it)
      {
        retVal = (*it)->find(name, maxDepth, level + 1);

        if (retVal != nullptr)
          break;
      }
    }

    return retVal;
  }

  /**
   * @brief Outputs the tree structure as a string.
   * @param stream Stream to output to
   * @param maxDepth Maximum recrusion depth
   * @param level Current level (do not set manually)
   */
  void SceneObject::printTree(std::ostream &stream, size_t maxDepth, size_t level)
  {
    for (size_t i = 0; i < level; i++)
      stream << ' ';

    stream << m_name << std::endl;

    if (level < maxDepth)
    {
      for (SceneObjectListIter it = m_children.begin(); it != m_children.end(); ++it)
        (*it)->printTree(stream, maxDepth, level + 1);
    }
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
