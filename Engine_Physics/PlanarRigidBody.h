/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_PLANARRIGIDBODY_H_
#define _ENGINE_PHYSICS_PLANARRIGIDBODY_H_

#include "RigidBody.h"

#include <btBulletDynamicsCommon.h>

namespace Engine
{
namespace Physics
{
  class PlanarRigidBody : public RigidBody
  {
  public:
    PlanarRigidBody(btMotionState *state, float mass, const btVector3 &inertia, const btVector3 &plane)
      : RigidBody(state, mass, inertia, new btStaticPlaneShape(plane, 1))
    {
    }
    
    virtual ~PlanarRigidBody()
    {
    }
  };
}
}

#endif
