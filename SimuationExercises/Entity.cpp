#include "Entity.h"

Entity::Entity()
  : m_aggroRange(0.0f)
  , m_entitiesInRange(0)
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
  m_aggroRange = aggroRange;
}