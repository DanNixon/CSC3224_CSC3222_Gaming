/**
 * @file
 * @author Dan Nixon
 */

#include "Entity.h"

#include <Random.h>

/**
 * @brief Creates an Entity with a randomised 2D position and aggro range.
 * @param symmLimit Limit for random number generation
 */
Entity::Entity(float symmLimit)
    : m_aggroRange2(0.0f)
    , m_entitiesInRange(0)
{
  if (symmLimit > 0.0f)
  {
    float aggroRange = Random::random(-symmLimit, symmLimit);
    m_aggroRange2 = aggroRange * aggroRange;

    m_position = Vector3(Random::random(-symmLimit, symmLimit),
                         Random::random(-symmLimit, symmLimit), 0.0f);
  }
}

/**
 * @brief Creates an Entity with a given position and aggro range.
 * @param pos Position
 * @param aggroRange Aggro range
 */
Entity::Entity(const Vector3 &pos, float aggroRange)
    : m_position(pos)
    , m_aggroRange2(aggroRange * aggroRange)
{
}

Entity::~Entity()
{
}

/**
 * @brief Sets the position of this Entity.
 * @param pos Position
 * @see Entity::position
 */
void Entity::setPosition(const Vector3 &pos)
{
  m_position = pos;
}

/**
 * @brief Sets the aggro range for this Entity.
 * @param aggroRange Aggro range
 * @see Entity::aggroRange2
 * @see Entity::aggroRange
 */
void Entity::setAggroRange(float aggroRange)
{
  m_aggroRange2 = aggroRange * aggroRange;
}

/**
 * @brief Outputs an Entity to a stream.
 * @param o Stream to output to
 * @param e Entity
 * @return Reference to stream
 */
std::ostream &operator<<(std::ostream &o, const Entity &e)
{
  o << "Entity[position=" << e.m_position << ",aggroRange=" << e.aggroRange()
    << "]";
  return o;
}
