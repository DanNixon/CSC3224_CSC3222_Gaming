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
     * @typedef InterfaceDef
     * @brief Type for recording an interface.
     *
     * In format {{first entity, second entity}, resolved flag}.
     */
    typedef std::pair<std::pair<Entity *, Entity *>, bool> InterfaceDef;

    PhysicsUpdate()
    {
    }

    virtual ~PhysicsUpdate()
    {
    }

    std::vector<InterfaceDef> interfaces()
    {
      return m_interfaces;
    }

    /**
     * @brief Performs all physics updates.
     * @param entities List of entities to update
     * @param dtMilliSec Time step in milliseconds
     */
    void update(Entity::EntityPtrList entities, float dtMilliSec)
    {
      // Perform position updates
      UpdatePositions(entities, dtMilliSec);

      // Detect interfaces
      detectInterfaces(entities);

      // Resolve interfaces
      resolveInterfaces();
    }

  private:
    static void UpdatePositions(Entity::EntityPtrList entities,
                                float dtMilliSec);

    void detectInterfaces(Entity::EntityPtrList entities);
    void resolveInterfaces();

  private:
    std::vector<InterfaceDef> m_interfaces;
  };
}
}

#endif
