/**
 * @file
 * @author Dan Nixon
 */

#include "Entity.h"

#include <Vector3.h>

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @brief Creates an Entity with a given position.
   * @param pos Position
   * @param stationary If this Entity is fixed in position
   * @param dragCoeff Velocity coefficient for simple drag simulation
   * @param velocityFloor Minimum velocity magnitude
   */
  Entity::Entity(const Vector2 &pos, bool stationary, float dragCoeff,
                 float velocityFloor)
      : m_stationary(stationary)
      , m_dragCoeff(dragCoeff)
      , m_velocityFloor2(velocityFloor * velocityFloor)
      , m_position(pos)
      , m_interface(false)
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
    m_position = pos;
  }

  /**
   * @brief Offsets the position of this Entity by a given amount.
   * @param offset Position offset
   * @see Entity::setPosition()
   * @see Entity::position()
   */
  void Entity::shiftPosition(const Vector2 &offset)
  {
    m_position += offset;
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

  bool Entity::clampVelocity()
  {
    bool clamp = (m_velocity.length2() < m_velocityFloor2);

    if (clamp)
      m_velocity.toZero();

    return clamp;
  }

  void Entity::multiplyDragCoeff()
  {
    m_velocity = m_velocity * m_dragCoeff;
  }
}
}
