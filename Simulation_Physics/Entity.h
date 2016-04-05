/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_PHYSICS_ENTITY_H_
#define _SIMULATION_PHYSICS_ENTITY_H_

#include <istream>
#include <list>
#include <vector>

#include <Engine_Graphics/BoundingBox.h>
#include <Engine_Maths/Vector2.h>

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
    /**
     * @typedef EntityPtrList
     * @brief List of pointers to Entity instances.
     */
    typedef std::vector<Entity *> EntityPtrList;

    /**
     * @typedef EntityPtrListIter
     * @brief Iterator ofver a list of pointers to Entity instances.
     */
    typedef EntityPtrList::iterator EntityPtrListIter;

    Entity(const Engine::Maths::Vector2 &pos, float mass, bool stationary = false, float dragCoeff = 1.0f,
           float velocityFloor = 0.0f);
    virtual ~Entity();

    /**
     * @brief Checks if this Entity is fixed in position.
     * @return True if stationary
     */
    bool stationary() const
    {
      return m_stationary;
    }

    Engine::Graphics::BoundingBox<Engine::Maths::Vector2> originBoundingBox() const
    {
      return m_originBox;
    }

    Engine::Graphics::BoundingBox<Engine::Maths::Vector2> boundingBox() const
    {
      return m_box;
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
     * @brief Gets the mass of this entity.
     * @return Mass
     */
    inline float mass() const
    {
      return 1.0f / m_inverseMass;
    }

    /**
     * @brief Gets the inverse mass of thiss entity.
     * @return 1 over mass
     */
    inline float inverseMass() const
    {
      return m_inverseMass;
    }

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

    friend std::ostream &operator<<(std::ostream &o, const Entity &e);

  private:
    bool clampVelocity();
    void multiplyDragCoeff();

  protected:
    friend class PhysicsSimulation;

    const bool m_stationary;      //!< Flag indicating this entity is stationary
    const float m_dragCoeff;      //!< Velocity coefficient due to simple drag
    const float m_velocityFloor2; //!< Velcoity magnitude squared at which
                                  // velocity is set to zero

    float m_inverseMass; //!< 1/mass
    Engine::Graphics::BoundingBox<Engine::Maths::Vector2> m_originBox;
    Engine::Graphics::BoundingBox<Engine::Maths::Vector2> m_box;
    Engine::Maths::Vector2 m_position;     //!< Position of Entity
    Engine::Maths::Vector2 m_velocity;     //!< Velocity in current timestep
    Engine::Maths::Vector2 m_acceleration; //!< Acceleration in current timestep
  };
}
}

#endif