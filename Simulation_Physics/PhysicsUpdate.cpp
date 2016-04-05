/**
 * @file
 * @author Dan Nixon
 */

#include "PhysicsUpdate.h"

#include <algorithm>

#include <Engine_Graphics/BoundingBox.h>
#include <Engine_Maths/Vector3.h>

#include "Integration.h"
#include "InterfaceDetection.h"
#include "InterfaceResolution.h"

using namespace Engine::Maths;
using namespace Engine::Graphics;

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
    // Sort entities along x-axis
    std::sort(entities.begin(), entities.end(),
              [](Entity *a, Entity *b) { return a->boundingBox().lowerLeft()[0] < b->boundingBox().lowerLeft()[0]; });

    std::vector<InterfaceDef> interfaces;

    // Create a list of possible interfaces (broadphase)
    for (Entity::EntityPtrListIter it = entities.begin(); it != entities.end(); ++it)
    {
      bool thisStationary = (*it)->stationary();
      float thisBoxRight = (*it)->boundingBox().upperRight()[0];

      for (auto iit = it + 1; iit != entities.end(); ++iit)
      {
        if (thisStationary && (*iit)->stationary())
          continue;

        float testBoxLeft = (*iit)->boundingBox().lowerLeft()[0];

        if (testBoxLeft < thisBoxRight)
          interfaces.push_back(InterfaceDef(*it, *iit));
      }
    }

    // Filter the list of possible interfaces to certain interfaces (narrowphase)
    for (auto it = interfaces.begin(); it != interfaces.end();)
    {
      if (InterfaceDetection::Detect(*it))
      {
        // Collision is valid
        ++it;
      }
      else
      {
        // No collision, remove the entry
        it = interfaces.erase(it);
      }
    }

    // Remove interfaces that have been resolved and are no longer detected
    for (auto it = m_interfaces.begin(); it != m_interfaces.end();)
    {
      // TODO: shouldn't need this check as all interfaces in this array should have already been resolved
      if (it->resolved())
      {
        auto i = std::find(interfaces.begin(), interfaces.end(), *it);

        if (i == interfaces.end())
          it = m_interfaces.erase(it);
        else
          ++it;
      }
    }

    // Add newly detected interfaces if it is not already detected
    for (auto it = interfaces.begin(); it != interfaces.end(); ++it)
    {
      auto i = std::find(m_interfaces.begin(), m_interfaces.end(), *it);

      if (i == m_interfaces.end())
        m_interfaces.push_back(*it);
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
