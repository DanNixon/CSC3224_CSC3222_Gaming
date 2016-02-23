/**
 * @file
 * @author Dan Nixon
 */

#include "PhysicsUpdate.h"

namespace Simulation
{
  namespace Physics
  {
    void PhysicsUpdate::UpdatePositions(Entity::EntityPtrList entities)
    {
      for (Entity::EntityPtrListIter it = entities.begin(); it != entities.end(); ++it)
      {
        if ((*it)->m_stationary)
          continue;

        // TODO
      }
    }

    void PhysicsUpdate::DetectInterfaces(Entity::EntityPtrList entities)
    {
      // TODO
    }
  }
}