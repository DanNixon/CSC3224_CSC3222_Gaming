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

    btCompoundShape *compoundShape = dynamic_cast<btCompoundShape *>(m_shape);
    if (compoundShape)
    {
      for (int i = 0; i < compoundShape->getNumChildShapes(); i++)
        delete compoundShape->getChildShape(i);
    }

    delete m_body->getMotionState();
    delete m_body;
    delete m_shape;
  }

  /**
   * @brief Extracts the up vector from this matrix.
   * @return Up direction vector
   */
  btVector3 RigidBody::upVector() const
  {
    return m_body->getWorldTransform().getBasis().getColumn(1);
  }

  /**
   * @brief Extracts the facing vector from this matrix.
   * @return Face direction vector
   */
  btVector3 RigidBody::facingVector() const
  {
    return m_body->getWorldTransform().getBasis().getColumn(0);
  }

  /**
   * @brief Extracts the left vector from this matrix.
   * @return Left direction vector
   */
  btVector3 RigidBody::leftVector() const
  {
    return -m_body->getWorldTransform().getBasis().getColumn(2);
  }
}
}
