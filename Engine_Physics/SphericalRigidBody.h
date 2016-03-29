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
  /**
   * @class SphericalRigidBody
   * @brief Represents a rigid body with spherical shape.
   * @author Dan Nixon
   */
  class SphericalRigidBody : public RigidBody
  {
  public:
    /**
     * @brief Creates a new rigid body of spherical shape.
     * @param state Motion state to be associated with body
     * @param mass Mass of body
     * @param inertia Inertia
     * @param radius Radius of the sphere
     */
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
