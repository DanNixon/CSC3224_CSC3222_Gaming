/**
 * @file
 * @author Dan Nixon
 */

#include "PhysicsUpdate.h"

#include <Vector3.h>

#include "Integration.h"

using namespace Engine::Maths;

namespace Simulation
{
  namespace Physics
  {
    void PhysicsUpdate::UpdatePositions(Entity::EntityPtrList entities, float dtMilliSec)
    {
      for (Entity::EntityPtrListIter it = entities.begin(); it != entities.end(); ++it)
      {
        if ((*it)->m_stationary)
          continue;

        // Calculate new velocity
        Integration::Euler<Vector2>((*it)->m_velocity, (*it)->m_velocity, (*it)->m_acceleration, dtMilliSec);
        if (!(*it)->clampVelocity())
          (*it)->multiplyDragCoeff();

        // Calculate new position/displacement
        Integration::Euler<Vector2>((*it)->m_position, (*it)->m_position, (*it)->m_velocity, dtMilliSec);

        // Update position
        (*it)->setPosition((*it)->m_position);
      }
    }

    void PhysicsUpdate::DetectInterfaces(Entity::EntityPtrList entities)
    {
      // TODO
    }
  }
}