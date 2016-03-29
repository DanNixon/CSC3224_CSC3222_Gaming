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
  /**
   * @class StaticPlaneRigidBody
   * @brief Represents a static rigid body along an infinite plane.
   * @author Dan Nixon
   */
  class StaticPlaneRigidBody : public RigidBody
  {
  public:
    /**
     * @brief Creates a new rigid body of planar shape.
     * @param state Motion state to be associated with body
     * @param mass Mass of body
     * @param inertia Inertia
     * @param plane Plane body exists in
     */
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
