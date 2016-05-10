/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _ENGINE_PHYSICS_COLLISIONCALLBACK_H_
#define _ENGINE_PHYSICS_COLLISIONCALLBACK_H_

#include <btBulletDynamicsCommon.h>

#include <Engine_ResourceManagment/IMemoryManaged.h>

namespace Engine
{
namespace Physics
{
  /**
   * @class CollisionCallback
   * @brief TODO
   * @author Dan Nixon
   */
  class CollisionCallback : public Engine::ResourceManagment::IMemoryManaged,
                            public btCollisionWorld::ContactResultCallback
  {
  public:
    CollisionCallback(btRigidBody &body)
        : btCollisionWorld::ContactResultCallback()
        , m_body(body)
    {
    }

    virtual ~CollisionCallback()
    {
    }

    virtual bool needsCollision(btBroadphaseProxy *proxy) const
    {
      if (!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
        return false;

      return m_body.checkCollideWithOverride(static_cast<btCollisionObject *>(proxy->m_clientObject));
    }

    virtual btScalar addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0, int partId0,
                                     int index0, const btCollisionObjectWrapper *colObj1, int partId1, int index1)
    {

      btVector3 pt;
      if (colObj0->m_collisionObject == &m_body)
      {
        pt = cp.m_localPointA;
      }
      else if (colObj1->m_collisionObject == &m_body)
      {
        pt = cp.m_localPointB;
      }
      else
      {
        return 0;
      }

      // do stuff with the collision point

      return 0;
    }

  private:
    btRigidBody &m_body;
  };
}
}
#endif
