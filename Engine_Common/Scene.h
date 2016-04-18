/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_COMMON_SCENE_H_
#define _ENGINE_COMMON_SCENE_H_

#include <Engine_Maths/Matrix4.h>
#include <Engine_ResourceManagment/IMemoryManaged.h>

#include "Subsystem.h"

namespace Engine
{
namespace Common
{
  class SceneObject;

  /**
   * @class Scene
   * @brief Represents a 3D scene.
   */
  class Scene : public Engine::ResourceManagment::IMemoryManaged
  {
  public:
    Scene(SceneObject *root, Engine::Maths::Matrix4 view = Engine::Maths::Matrix4(),
          Engine::Maths::Matrix4 projection = Engine::Maths::Matrix4());
    virtual ~Scene();

    void setViewMatrix(Engine::Maths::Matrix4 view);
    Engine::Maths::Matrix4 viewMatrix();

    void setProjectionMatrix(Engine::Maths::Matrix4 projection);
    Engine::Maths::Matrix4 projectionMatrix();

    virtual void update(float msec, Subsystem sys);

    /**
     * @brief Gets the root node of the scene.
     * @return Root node
     */
    SceneObject *root()
    {
      return m_root;
    }

  protected:
    SceneObject *m_root;                       //!< Root node in the scene tree
    Engine::Maths::Matrix4 m_viewMatrix;       //!< View matrix
    Engine::Maths::Matrix4 m_projectionMatrix; //!< Projection matrix
  };
}
}

#endif
