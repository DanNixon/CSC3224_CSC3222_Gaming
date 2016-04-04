/**
 * @file
 * @author Dan Nixon
 */

#include "PhysicsUpdate.h"

#include <algorithm>

#include <Engine_Maths/Vector3.h>

#include "Integration.h"
#include "InterfaceDetection.h"
#include "InterfaceResolution.h"

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

  /**
   * @brief Detects interfaces between entities.
   * @param entities List of entities to update
   */
  void PhysicsUpdate::detectInterfaces(Entity::EntityPtrList entities)
  {
    // TODO: use sort and sweep along x axis

    for (Entity::EntityPtrListIter oit = entities.begin(); oit != entities.end();)
    {
      for (Entity::EntityPtrListIter iit = entities.begin(); iit != entities.end(); ++iit)
      {
        // Don't comapre the same entity
        if (*oit == *iit)
          continue;

        // Don't compare two stationary entities
        if ((*oit)->stationary() && (*iit)->stationary())
          continue;

        InterfaceDef interf(*oit, *iit);

        // Check for interface
        bool detected = InterfaceDetection::Detect(interf);

        auto it = std::find(m_interfaces.begin(), m_interfaces.end(), interf);

        // Remove a resolved interface that is no longer detected
        if (it != m_interfaces.end() && !(detected || !it->m_resolved))
          m_interfaces.erase(it);

        // Add a newly detected interface if it is not already detected
        if (detected && it == m_interfaces.end())
          m_interfaces.push_back(interf);
      }

      oit = entities.erase(oit);
    }
  }

  /**
   * @brief Resolves detected interfaces.
   * @param entities List of entities to update
   */
  void PhysicsUpdate::resolveInterfaces()
  {
    for (auto it = m_interfaces.begin(); it != m_interfaces.end(); ++it)
    {
      // If the interface is yet to be resolved
      if (!it->m_resolved)
      {
        InterfaceResolution::Impulse(*it, 0.5f);

        // Mark the interface as having been resolved
        it->m_resolved = true;
      }
    }
  }
}
}
