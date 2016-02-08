#pragma once

#include "Vector3.h"

class Entity
{
public:
  Entity();
  virtual ~Entity();

  inline Vector3 position() const
  {
    return m_position;
  }

  void setPosition(const Vector3 &pos);

  inline float aggroRange() const
  {
    return m_aggroRange;
  }

  void setAggroRange(float aggroRange);

  inline int entitiesInRange() const
  {
    return m_entitiesInRange;
  }

private:
  Vector3 m_position;
  float m_aggroRange;
  int m_entitiesInRange;
};

