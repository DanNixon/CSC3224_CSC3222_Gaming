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
    class PlanarEntity : public Entity
    {
    public:
      PlanarEntity(const Engine::Maths::Vector2 &pos);
      virtual ~PlanarEntity();
    };
  }
}