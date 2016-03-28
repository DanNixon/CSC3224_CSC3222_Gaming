/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_SPHERICALRIGIDBODY_H_
#define _ENGINE_PHYSICS_SPHERICALRIGIDBODY_H_

#include "RigidBody.h"

#include <btBulletDynamicsCommon.h>

namespace Engine
{
namespace Physics
{
  class SphericalRigidBody : public RigidBody
  {
  public:
    SphericalRigidBody(btMotionState *state, float mass, const btVector3 &inertia, float radius)
      : RigidBody(state, mass, inertia, new btSphereShape(radius))
    {
    }
    
    virtual ~SphericalRigidBody()
    {
    }
  };
}
}

#endif
