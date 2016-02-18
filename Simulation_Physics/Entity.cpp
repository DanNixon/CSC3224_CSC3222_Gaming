#include "Entity.h"

#include <Random.h>

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

Entity::Entity(const Vector3 &pos, float aggroRange)
    : m_position(pos)
    , m_aggroRange2(aggroRange * aggroRange)
{
}

Entity::~Entity()
{
}

void Entity::setPosition(const Vector3 &pos)
{
  m_position = pos;
}

void Entity::setAggroRange(float aggroRange)
{
  m_aggroRange2 = aggroRange * aggroRange;
}

std::ostream &operator<<(std::ostream &o, const Entity &e)
{
  o << "Entity[position=" << e.m_position << ",aggroRange=" << e.aggroRange()
    << "]";
  return o;
}