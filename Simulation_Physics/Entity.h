/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <istream>

#include <Vector2.h>

namespace Simulation
{
namespace Physics
{
  /**
   * @class Entity
   * @brief Represents an entity in a simulation.
   * @author Dan Nixon
   */
  class Entity
  {
  public:
    Entity(float symmLimit);
    Entity(const Engine::Maths::Vector2 &pos);
    virtual ~Entity();

    /**
     * @brief Gets the position of this entity.
     * @return Position
     * @see Entity::setPosition
     */
    inline Engine::Maths::Vector2 position() const
    {
      return m_position;
    }

    void setPosition(const Engine::Maths::Vector2 &pos);

  private:
    Engine::Maths::Vector2 m_position; //!< Position of Entity
  };
}
}
