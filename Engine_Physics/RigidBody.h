/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_RIGIDBODY_H_
#define _ENGINE_PHYSICS_RIGIDBODY_H_

#include <btBulletDynamicsCommon.h>

#include <IMemoryManaged.h>

#include "SceneObjectMotionState.h"

namespace Engine
{
namespace Physics
{
  class PhysicalSystem;

  class RigidBody : public Engine::Common::IMemoryManaged
  {
  public:
    RigidBody(btMotionState *state, float mass, const btVector3 &inertia, btCollisionShape *shape);
    virtual ~RigidBody();

    /**
     * @copydoc IMemoryManaged::releaseOrder
     */
    virtual int releaseOrder() const
    {
      return 40;
    }

    inline btMotionState *motionState()
    {
      return m_body->getMotionState();
    }

  protected:
    friend class PhysicalSystem;

    btRigidBody *m_body;
    btCollisionShape *m_shape;

    PhysicalSystem *m_system;
  };
}
}

#endif
