/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_SCENEOBJECTMOTIONSTATE_H_
#define _ENGINE_PHYSICS_SCENEOBJECTMOTIONSTATE_H_

#include <btBulletDynamicsCommon.h>

#include <SceneObject.h>

namespace Engine
{
namespace Physics
{
  class SceneObjectMotionState : public btMotionState
  {
  public:
    SceneObjectMotionState(const btTransform &initialPosition, Engine::Common::SceneObject *object);
    virtual ~SceneObjectMotionState();

    void setSceneObject(Engine::Common::SceneObject *object);

    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);

  protected:
    btTransform m_initialPosition;
    Engine::Common::SceneObject *m_sceneObject;
  };
}
}

#endif