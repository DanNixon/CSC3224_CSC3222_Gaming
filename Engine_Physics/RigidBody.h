/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_RIGIDBODY_H_
#define _ENGINE_PHYSICS_RIGIDBODY_H_

#include <btBulletDynamicsCommon.h>

namespace Engine
{
namespace Physics
{
  class RigidBody : public btRigidBody
  {
  public:
    RigidBody();
    virtual ~RigidBody();
  };
}
}

#endif
