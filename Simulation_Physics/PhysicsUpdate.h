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
      static void Update(Entity::EntityPtrList entities, float dtMilliSec)
      {
        UpdatePositions(entities, dtMilliSec);
        DetectInterfaces(entities);
      }

    private:
      static void UpdatePositions(Entity::EntityPtrList entities, float dtMilliSec);
      static void DetectInterfaces(Entity::EntityPtrList entities);
    };
  }
}