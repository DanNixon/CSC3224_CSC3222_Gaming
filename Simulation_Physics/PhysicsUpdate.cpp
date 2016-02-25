/**
 * @file
 * @author Dan Nixon
 */

#include "PhysicsUpdate.h"

#include <Vector3.h>

#include "Integration.h"
#include "InterfaceDetection.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @brief Updates the positions of entities according to their velocity and
   *        acceleration.
   * @param entities List of entities to update
   * @param dtMilliSec Time step in milliseconds
   */
  void PhysicsUpdate::UpdatePositions(Entity::EntityPtrList entities,
                                      float dtMilliSec)
  {
    for (Entity::EntityPtrListIter it = entities.begin(); it != entities.end();
         ++it)
    {
      if ((*it)->m_stationary)
        continue;

      // Calculate new velocity
      Integration::Euler<Vector2>((*it)->m_velocity, (*it)->m_velocity,
                                  (*it)->m_acceleration, dtMilliSec);
      if (!(*it)->clampVelocity())
        (*it)->multiplyDragCoeff();

      // Calculate new position/displacement
      Integration::Euler<Vector2>((*it)->m_position, (*it)->m_position,
                                  (*it)->m_velocity, dtMilliSec);

      // Update position
      (*it)->setPosition((*it)->m_position);
    }
  }

  /**
   * @brief Detects interfaces between entities.
   * @param entities List of entities to update
   */
  void PhysicsUpdate::DetectInterfaces(Entity::EntityPtrList entities)
  {
    for (Entity::EntityPtrListIter oit = entities.begin();
         oit != entities.end(); ++oit)
    {
      for (Entity::EntityPtrListIter iit = entities.begin();
           iit != entities.end(); ++iit)
      {
        if (*oit == *iit)
          continue;

        // Check for interface
        if (InterfaceDetection::Detect(**oit, **iit))
        {
          // Set interface flag
          (*oit)->m_interface = true;
          (*iit)->m_interface = true;
        }
      }
    }
  }

  /**
   * @brief Resolves detected interfaces.
   * @param entities List of entities to update
   */
  void PhysicsUpdate::ResolveInterfaces(Entity::EntityPtrList entities)
  {
    for (Entity::EntityPtrListIter it = entities.begin(); it != entities.end();
         ++it)
    {
      // TODO
    }
  }
}
}
