/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <istream>
#include <list>

#include <Vector2.h>

namespace Simulation
{
namespace Physics
{
  /**
   * @class Entity
   * @brief Represents an entity in a 2D simulation.
   * @author Dan Nixon
   */
  class Entity
  {
  public:
    typedef std::list<Entity *> EntityPtrList;
    typedef EntityPtrList::iterator EntityPtrListIter;

    Entity(const Engine::Maths::Vector2 &pos, bool stationary = false, float dragCoeff = 1.0f, float velocityFloor = 0.0f);
    virtual ~Entity();

    /**
     * @brief Checks if this Entity is fixed in position.
     * @return True if stationary
     */
    bool stationary() const
    {
      return m_stationary;
    }

    /**
     * @brief Gets the position of this entity.
     * @return Position
     * @see Entity::setPosition()
     * @see Entity::shiftPosition()
     */
    inline Engine::Maths::Vector2 position() const
    {
      return m_position;
    }

    virtual void setPosition(const Engine::Maths::Vector2 &pos);
    virtual void shiftPosition(const Engine::Maths::Vector2 &offset);

    /**
     * @brief Gets the velocity of this entity in the current timestep.
     * @return Velocity
     * @see Entity::setVelocity()
     */
    inline Engine::Maths::Vector2 velocity() const
    {
      return m_velocity;
    }

    void setVelocity(const Engine::Maths::Vector2 &vel);

    /**
     * @brief Gets the acceleration of this entity in the current timestep.
     * @return Acceleration
     * @see Entity::setAcceleration()
     */
    inline Engine::Maths::Vector2 acceleration() const
    {
      return m_acceleration;
    }

    void setAcceleration(const Engine::Maths::Vector2 &acc);

  private:
    friend class PhysicsUpdate;

    bool clampVelocity();
    void multiplyDragCoeff();

    const bool m_stationary; //!< Flag indicating this entity is stationary
    const float m_dragCoeff; //!< Velocity coefficient due to simple drag
    const float m_velocityFloor2; //<! Velcoity magnitude squared at which velocity is set to zero

    Engine::Maths::Vector2 m_position; //!< Position of Entity
    Engine::Maths::Vector2 m_velocity; //!< Velocity in current timestep
    Engine::Maths::Vector2 m_acceleration; //!< Acceleration in current timestep
    bool m_interface; //!< Flag indicating interface detection
  };
}
}
