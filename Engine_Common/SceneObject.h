/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_COMMON_SCENEOBJECT_H_
#define _ENGINE_COMMON_SCENEOBJECT_H_

#include <vector>

#include "Matrix4.h"
#include "Scene.h"

namespace Engine
{
namespace Common
{
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

    SceneObject(const std::string &name);
    ~SceneObject();

    inline std::string name() const
    {
      return m_name;
    }

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

    /**
     * @brief Sets the position of this object relative to its parent.
     * @param mat Model matrix
     */
    void setModelMatrix(Engine::Maths::Matrix4 mat)
    {
      m_modelMatrix = mat;
    }

    /**
     * @brief Gets the model matrix (relative to parent)
     * @return Model matrix
     */
    inline Engine::Maths::Matrix4 modelMatrix() const
    {
      return m_modelMatrix;
    }

    /**
     * @brief Gets the position in world space (absolute position)
     * @return World position
     */
    inline Engine::Maths::Matrix4 worldTransform() const
    {
      return m_worldTransform;
    }

    virtual void update(float msec);
    virtual void render();

    SceneObject * findChild(const std::string &name);

  protected:
    friend class Scene;

    void addToScene(Scene *scene);

    const std::string m_name;

    Engine::Maths::Matrix4
        m_modelMatrix; //!< Local model matrix (relative to parent)
    Engine::Maths::Matrix4
        m_worldTransform; //!< World matrix (relative to world origin)

    SceneObject *m_parent;                 //!< Parent SceneObject
    Scene *m_scene;                        //!< Scene this object belongs to
    std::vector<SceneObject *> m_children; //!< Children
  };
}
}

#endif