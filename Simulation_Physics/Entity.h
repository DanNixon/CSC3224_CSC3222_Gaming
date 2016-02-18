#pragma once

#include "Vector3.h"

class Entity
{
public:
  Entity(float symmLimit);
  Entity(const Vector3 &pos, float aggroRange);
  virtual ~Entity();

  inline Vector3 position() const
  {
    return m_position;
  }

  void setPosition(const Vector3 &pos);

  inline float aggroRange() const
  {
    return sqrt(m_aggroRange2);
  }

  inline float aggroRange2() const
  {
    return m_aggroRange2;
  }

  void setAggroRange(float aggroRange);

  inline int entitiesInRange() const
  {
    return m_entitiesInRange;
  }

  inline int &entitiesInRangeRef()
  {
    return m_entitiesInRange;
  }

  friend std::ostream &operator<<(std::ostream &o, const Entity &e);

private:
  Vector3 m_position;
  float m_aggroRange2;
  int m_entitiesInRange;
};
