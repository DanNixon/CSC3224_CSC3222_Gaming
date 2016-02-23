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
    class PhysicsUpdate
    {
    public:
      static void Update(Entity::EntityPtrList entities)
      {
        UpdatePositions(entities);
        DetectInterfaces(entities);
      }

    private:
      static void UpdatePositions(Entity::EntityPtrList entities);
      static void DetectInterfaces(Entity::EntityPtrList entities);
    };
  }
}