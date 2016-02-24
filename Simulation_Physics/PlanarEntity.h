/**
* @file
* @author Dan Nixon
*/

#pragma once

#include "Entity.h"

namespace Simulation
{
namespace Physics
{
  /**
   * @class PlanarEntity
   * @brief Represents an entity that exists along a 2D plane.
   * @author Dan Nixon
   */
  class PlanarEntity : public Entity
  {
  public:
    PlanarEntity(const Engine::Maths::Vector2 &pos, int direction);
    virtual ~PlanarEntity();

    int direction() const
    {
      return m_direction;
    }

    int axis() const;

  private:
    int m_direction;
  };
}
}
