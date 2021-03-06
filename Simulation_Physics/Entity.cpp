/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#include "Entity.h"

#include <Engine_Maths/Vector3.h>

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @brief Creates an Entity with a given position.
   * @param pos Position
   * @param mass Mass of the entity
   * @param stationary If this Entity is fixed in position
   * @param dragCoeff Velocity coefficient for simple drag simulation
   * @param velocityFloor Minimum velocity magnitude
   */
  Entity::Entity(const Vector2 &pos, float mass, bool stationary, float dragCoeff, float velocityFloor)
      : m_stationary(stationary)
      , m_collides(true)
      , m_dragCoeff(dragCoeff)
      , m_velocityFloor2(velocityFloor * velocityFloor)
      , m_inverseMass(1.0f / mass)
      , m_position(pos)
  {
  }

  Entity::~Entity()
  {
  }

  /**
   * @brief Sets the position of this Entity.
   * @param pos Position
   * @see Entity::shiftPosition()
   * @see Entity::position()
   */
  void Entity::setPosition(const Vector2 &pos)
  {
    if (!m_stationary)
    {
      m_position = pos;

      m_box = m_originBox;
      m_box += pos;
    }
  }

  /**
   * @brief Offsets the position of this Entity by a given amount.
   * @param offset Position offset
   * @see Entity::setPosition()
   * @see Entity::position()
   */
  void Entity::shiftPosition(const Vector2 &offset)
  {
    if (!m_stationary)
    {
      m_position += offset;

      m_box = m_originBox;
      m_box += m_position;
    }
  }

  /**
   * @brief Sets the velocity of this Entity in the current timestep.
   * @param vel Velocity
   * @see Entity::velocity()
   */
  void Entity::setVelocity(const Vector2 &vel)
  {
    m_velocity = vel;
  }

  /**
   * @brief Sets the acceleration of this Entity in the current timestep.
   * @param acc Acceleration
   * @see Entity::acceleration()
   */
  void Entity::setAcceleration(const Vector2 &acc)
  {
    m_acceleration = acc;
  }

  /**
   * @brief Immediately stops this entity moving.
   */
  void Entity::stopMotion()
  {
    m_acceleration.toZero();
    m_velocity.toZero();
  }

  /**
   * @brief Clamps the velocity of this Entity it its lower limit.
   * @return True if the velocity was clamped
   */
  bool Entity::clampVelocity()
  {
    bool clamp = (m_velocity.length2() < m_velocityFloor2);

    if (clamp)
      m_velocity.toZero();

    return clamp;
  }

  /**
   * @brief Multiplies the velocity of this Entity by its drag coefficient.
   */
  void Entity::multiplyDragCoeff()
  {
    m_velocity = m_velocity * m_dragCoeff;
  }

  /**
   * @brief Outputs this Entity to a stream in a friendly format.
   * @param o Stream
   * @param e Entity
   * @return Stream
   */
  std::ostream &operator<<(std::ostream &o, const Entity &e)
  {
    o << "Entity["
      << "stationary=" << e.m_stationary << ",mass=" << e.mass() << ",position=" << e.m_position
      << ",velocity=" << e.m_velocity << ",acceleration=" << e.m_acceleration << "]";

    return o;
  }
}
}
