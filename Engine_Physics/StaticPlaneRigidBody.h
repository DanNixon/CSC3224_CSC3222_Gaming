/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_STATICPLANERIGIDBODY_H_
#define _ENGINE_PHYSICS_STATICPLANERIGIDBODY_H_

#include "RigidBody.h"

#include <btBulletDynamicsCommon.h>

namespace Engine
{
namespace Physics
{
  class StaticPlaneRigidBody : public RigidBody
  {
  public:
    StaticPlaneRigidBody(btMotionState *state, float mass, const btVector3 &inertia, const btVector3 &plane)
        : RigidBody(state, mass, inertia, new btStaticPlaneShape(plane, 0.0f))
    {
    }

    virtual ~StaticPlaneRigidBody()
    {
    }
  };
}
}

#endif
