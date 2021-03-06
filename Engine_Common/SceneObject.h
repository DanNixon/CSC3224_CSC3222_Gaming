/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_COMMON_SCENEOBJECT_H_
#define _ENGINE_COMMON_SCENEOBJECT_H_

#include <vector>

#include <Engine_Maths/Matrix4.h>
#include <Engine_ResourceManagment/IMemoryManaged.h>

#include "Scene.h"
#include "Subsystem.h"

namespace Engine
{
namespace Common
{
  /**
   * @class SceneObject
   * @brief Represents an item in a Scene.
   */
  class SceneObject : public Engine::ResourceManagment::IMemoryManaged
  {
  public:
    /**
     * @typedef SceneObjectList
     * @brief List of pointers to SceneObject.
     */
    typedef std::vector<SceneObject *> SceneObjectList;

    /**
     * @typedef SceneObjectListIter
     * @brief Const iterator for items of a SceneObjectList.
     */
    typedef SceneObjectList::const_iterator SceneObjectListIter;

    SceneObject(const std::string &name, SceneObject *parent = nullptr);
    ~SceneObject();

    /**
     * @brief Gets the name of the object.
     * @return Object name
     */
    inline std::string name() const
    {
      return m_name;
    }

    void setActive(bool active, size_t recursionLevels = std::numeric_limits<size_t>::max(), size_t currentLevel = 0);

    /**
     * @brief Gets the active state of this object.
     * @return Active
     */
    inline bool active() const
    {
      return m_active;
    }

    /**
     * @brief Gets a pointer to the parent object.
     * @return Parent
     */
    inline SceneObject *parent()
    {
      return m_parent;
    }

    /**
     * @brief Adds a SceneObject as a child of this object.
     * @param child Child SceneObject
     */
    void addChild(SceneObject *child)
    {
      m_children.push_back(child);
      child->m_parent = this;
      child->addToScene(m_scene);
    }

    /**
     * @brief Removes a child SceneObject from this object.
     * @param child Child SceneObject
     */
    void removeChild(SceneObject *child)
    {
      auto it = std::find(m_children.begin(), m_children.end(), child);
      if (it != m_children.end())
      {
        m_children.erase(it);
        child->m_parent = nullptr;
        child->addToScene(nullptr);
      }
    }

    /**
     * @brief Gets the list of children SceneObject of this object.
     * @return List of children
     * @see SceneObject::numChildren()
     */
    const std::vector<SceneObject *> &children() const
    {
      return m_children;
    }

    /**
     * @brief Gets the number of children SceneObject of this object.
     * @return Number of children
     * @see SceneObject::children()
     */
    size_t numChildren() const
    {
      return m_children.size();
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

    virtual void update(float msec, Subsystem sys);

    SceneObject *find(const std::string &name, size_t maxDepth = std::numeric_limits<size_t>::max(), size_t level = 0);
    void printTree(std::ostream &stream, size_t maxDepth = std::numeric_limits<size_t>::max(), size_t level = 0);

  protected:
    friend class Scene;

    virtual void addToScene(Scene *scene);

    const std::string m_name; //!< Name of the object
    bool m_active;            //!< Flag indicating if this object is active in the scene

    Engine::Maths::Matrix4 m_modelMatrix;    //!< Local model matrix (relative to parent)
    Engine::Maths::Matrix4 m_worldTransform; //!< World matrix (relative to world origin)

    SceneObject *m_parent;      //!< Parent SceneObject
    Scene *m_scene;             //!< Scene this object belongs to
    SceneObjectList m_children; //!< Children
  };
}
}

#endif
