/**
 * @file
 * @author Dan Nixon
 */

#include "RigidBody.h"

#include "PhysicalSystem.h"

namespace Engine
{
namespace Physics
{
  RigidBody::RigidBody(btMotionState *state, float mass, const btVector3 &inertia, btCollisionShape *shape)
      : m_body(nullptr)
      , m_shape(shape)
      , m_system(nullptr)
  {
    btVector3 localInertia(inertia);
    m_shape->calculateLocalInertia(mass, localInertia);

    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(mass, state, m_shape, localInertia);
    m_body = new btRigidBody(groundRigidBodyCI);
  }

  RigidBody::~RigidBody()
  {
    if (m_system != nullptr)
      m_system->removeBody(this);

    delete m_body->getMotionState();
    delete m_body;
    delete m_shape;
  }
}
}
