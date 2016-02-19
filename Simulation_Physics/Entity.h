/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "Vector3.h"

/**
 * @class Entity
 * @brief Represents an entity in a simulation.
 * @author Dan Nixon
 */
class Entity
{
public:
  Entity(float symmLimit);
  Entity(const Vector3 &pos, float aggroRange);
  virtual ~Entity();

  /**
   * @brief Gets the position of this entity.
   * @return Position
   * @see Entity::setPosition
   */
  inline Vector3 position() const
  {
    return m_position;
  }

  void setPosition(const Vector3 &pos);

  /**
   * @brief Gets the aggro range of this entity.
   * @return Aggro range
   * @see Entity::aggroRange2
   * @see Entity::setAggroRange
   */
  inline float aggroRange() const
  {
    return sqrt(m_aggroRange2);
  }

  /**
   * @brief Gets the squared aggro range of this entity.
   * @return Aggro range squared
   * @see Entity::aggroRange
   * @see Entity::setAggroRange
   */
  inline float aggroRange2() const
  {
    return m_aggroRange2;
  }

  void setAggroRange(float aggroRange);

  /**
   * @brief Gets the number of Entities within the aggro range of this Entity.
   * @return Entities in range
   */
  inline int entitiesInRange() const
  {
    return m_entitiesInRange;
  }

  /**
   * @brief Returns a reference to the number of Entities within the aggro
   *        range of this Entity.
   * @return Entities in range
   */
  inline int &entitiesInRangeRef()
  {
    return m_entitiesInRange;
  }

  friend std::ostream &operator<<(std::ostream &o, const Entity &e);

private:
  Vector3 m_position;    //!< Position of Entity
  float m_aggroRange2;   //!< Aggro range squared
  int m_entitiesInRange; //!< Number of entities within aggro range
};
