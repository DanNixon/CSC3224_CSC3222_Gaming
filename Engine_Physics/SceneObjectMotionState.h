/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_PHYSICS_SCENEOBJECTMOTIONSTATE_H_
#define _ENGINE_PHYSICS_SCENEOBJECTMOTIONSTATE_H_

#include <btBulletDynamicsCommon.h>

#include <Engine_Common/SceneObject.h>
#include <Engine_Maths/QUaternion.h>
#include <Engine_Maths/Vector3.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class SceneObjectMotionState
   * @brief Motion state for SceneObject instances.
   * @author Dan Nixon
   */
  class SceneObjectMotionState : public btMotionState
  {
  public:
    SceneObjectMotionState(Engine::Common::SceneObject *object, const Engine::Maths::Vector3 &initialPos,
                           Engine::Maths::Quaternion initialRot);
    virtual ~SceneObjectMotionState();

    void setSceneObject(Engine::Common::SceneObject *object);

    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);

  protected:
    Engine::Common::SceneObject *m_sceneObject; //!< Target scene object
    btTransform m_initial;                      //!< Initial position and orientation of the object
  };
}
}

#endif
