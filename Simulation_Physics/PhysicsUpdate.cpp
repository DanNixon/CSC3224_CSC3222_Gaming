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
    // Detected interfaces
    std::vector<InterfaceDef> interfaces;

    // Run sort and sweep along x-axis
    std::sort(entities.begin(), entities.end(),
              [](Entity *a, Entity *b) { return a->position()[0] < b->position()[0]; });

    // Remove entities that cannot be interfacing
    for (Entity::EntityPtrListIter it = entities.begin() + 1; it != entities.end() - 1;)
    {
      // std::cout << it - entities.begin() << std::endl;

      BoundingBox<Vector2> thisBox = (*it)->boundingBox();
      float thisLeft = thisBox.lowerLeft()[0];
      float thisRight = thisBox.upperRight()[0];

      float left = (*(it - 1))->boundingBox().upperRight()[0];
      float right = (*(it + 1))->boundingBox().lowerLeft()[0];

      // Check for projection intersection
      if (left < thisLeft && thisRight < right)
      {
        // TODO

        // cannot intersect any entities
      }

      ++it;
    }

    // TODO

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
        if (InterfaceDetection::Detect(interf))
        {
          interfaces.push_back(interf);
        }
      }

      oit = entities.erase(oit);
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
