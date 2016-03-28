/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_PHYSICS_PHYSICALSYSTEM_H_
#define _ENGINE_PHYSICS_PHYSICALSYSTEM_H_

#include <btBulletDynamicsCommon.h>

#include <IMemoryManaged.h>

#include "RigidBody.h"

namespace Engine
{
namespace Physics
{
  class PhysicalSystem : public Engine::Common::IMemoryManaged
  {
  public:
    PhysicalSystem();
    virtual ~PhysicalSystem();

    /**
     * @copydoc IMemoryManaged::releaseOrder
     */
    virtual int releaseOrder() const
    {
      return 50;
    }

    void addBody(RigidBody *body);
    void removeBody(RigidBody *body);

    void update(float msec);

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
