/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_SCENEOBJECTMOTIONSTATE_H_
#define _ENGINE_PHYSICS_SCENEOBJECTMOTIONSTATE_H_

#include <btBulletDynamicsCommon.h>

#include <SceneObject.h>
#include <Vector3.h>
#include <QUaternion.h>

namespace Engine
{
namespace Physics
{
  class SceneObjectMotionState : public btMotionState
  {
  public:
    SceneObjectMotionState(Engine::Common::SceneObject *object,
        const Engine::Maths::Vector3 &initialPos,
        const Engine::Maths::Quaternion & initialRot);
    virtual ~SceneObjectMotionState();

    void setSceneObject(Engine::Common::SceneObject *object);

    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);

  protected:
    Engine::Common::SceneObject *m_sceneObject;
    btTransform m_initialPosition;
  };
}
}

#endif