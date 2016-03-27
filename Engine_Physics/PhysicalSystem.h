/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_PHYSICALSYSTEM_H_
#define _ENGINE_PHYSICS_PHYSICALSYSTEM_H_

#include <btBulletDynamicsCommon.h>

namespace Engine
{
namespace Physics
{
  class PhysicalSystem
  {
  public:
    PhysicalSystem();
    virtual ~PhysicalSystem();

  private:
    btBroadphaseInterface *m_broadphase;
    btDefaultCollisionConfiguration *m_collisionConfig;
    btCollisionDispatcher *m_collisionDispatcher;
    btSequentialImpulseConstraintSolver *m_solver;
    btDiscreteDynamicsWorld *m_world;
  };
}
}

#endif
