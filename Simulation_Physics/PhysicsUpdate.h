/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_PHYSICS_PHYSICSUPDATE_H_
#define _SIMULATION_PHYSICS_PHYSICSUPDATE_H_

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
      // Clear interface flags
      for (Entity::EntityPtrListIter it = entities.begin();
           it != entities.end(); ++it)
        (*it)->m_interface = false;

      // Perform updates
      UpdatePositions(entities, dtMilliSec);
      DetectInterfaces(entities);
      ResolveInterfaces(entities);
    }

  private:
    static void UpdatePositions(Entity::EntityPtrList entities,
                                float dtMilliSec);
    static void DetectInterfaces(Entity::EntityPtrList entities);
    static void ResolveInterfaces(Entity::EntityPtrList entities);
  };
}
}

#endif