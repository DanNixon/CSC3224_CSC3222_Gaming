/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "RigidBody.h"

#include "PhysicalSystem.h"

namespace Engine
{
namespace Physics
{
  /**
   * @brief Creates a new rigid body.
   * @param state Motion state to be associated with body
   * @param mass Mass of body
   * @param inertia Inertia
   * @param shape Shape of body
   */
  RigidBody::RigidBody(btMotionState *state, float mass, const btVector3 &inertia, btCollisionShape *shape)
      : m_body(nullptr)
      , m_shape(shape)
      , m_system(nullptr)
  {
    btVector3 localInertia(inertia);

    if (mass > 0.0f)
      m_shape->calculateLocalInertia(mass, localInertia);

    btRigidBody::btRigidBodyConstructionInfo bodyCI(mass, state, m_shape, localInertia);
    m_body = new btRigidBody(bodyCI);
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
