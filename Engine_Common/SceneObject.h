/** @file */

#pragma once

#include <vector>

#include "Matrix4.h"
#include "Scene.h"

/**
 * @class SceneObject
 * @brief Represents an item in a Scene.
 */
class SceneObject
{
public:
  /**
   * @typedef SceneObjectIter
   * @brief Const iterator for items of a vector of SceneObject.
   */
  typedef std::vector<SceneObject *>::const_iterator SceneObjectIter;

  SceneObject();
  ~SceneObject();

  /**
   * @brief Adds a SceneObject as a child of this object.
   * @param child Child SceneObject
   */
  void addChild(SceneObject &child)
  {
    m_children.push_back(&child);
    child.m_parent = this;
    child.m_scene = m_scene;
  }

  /**
   * @brief Gets the list of children SceneObject of this object.
   * @return List of children
   */
  const std::vector<SceneObject *> &children() const
  {
    return m_children;
  }

  void setModelMatrix(Matrix4 mat)
  {
    m_modelMatrix = mat;
  }

  Matrix4 modelMatrix() const
  {
    return m_modelMatrix;
  }

  Matrix4 worldTransform() const
  {
    return m_worldTransform;
  }

  virtual void update(float msec);
  virtual void render();

protected:
  friend class Scene;

  void addToScene(Scene *scene);

  Matrix4 m_modelMatrix;    //!< Local model matrix (relative to parent)
  Matrix4 m_worldTransform; //!< World matrix (relative to world origin)

  SceneObject *m_parent;                 //!< Parent SceneObject
  Scene *m_scene;                        //!< Scene this object belongs to
  std::vector<SceneObject *> m_children; //!< Children
};
