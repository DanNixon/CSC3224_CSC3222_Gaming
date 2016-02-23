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
     * @class PhysicsUpdate
     * @brief Contains utilities for performing physics updates.
     * @author Dan Nixon
     */
    class PhysicsUpdate
    {
    public:
      /**
       * @brief Performs all physics updates.
       * @param entities List of entities to update
       * @param dtMilliSec Time step in milliseconds
       */
      static void Update(Entity::EntityPtrList entities, float dtMilliSec)
      {
        UpdatePositions(entities, dtMilliSec);
        DetectInterfaces(entities);
        ResolveInterfaces(entities);
      }

    private:
      static void UpdatePositions(Entity::EntityPtrList entities, float dtMilliSec);
      static void DetectInterfaces(Entity::EntityPtrList entities);
      static void ResolveInterfaces(Entity::EntityPtrList entities);
    };
  }
}
