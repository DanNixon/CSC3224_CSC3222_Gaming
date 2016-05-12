/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "FSPhysicalSystem.h"

#include <sstream>

using namespace Engine::Common;
using namespace Engine::Physics;
using namespace Engine::Utility;

namespace GameDev
{
namespace FlightSim
{
  /**
   * @copdoc PhysicalSystem::PhysicalSystem
   * @param game Pointer to the game instance in use
   */
  FSPhysicalSystem::FSPhysicalSystem(float targetTimeStep, float maxPossibleTimeStep, float worldScale, Game *game)
      : PhysicalSystem(targetTimeStep, maxPossibleTimeStep, worldScale)
      , m_game(game)
  {
  }

  FSPhysicalSystem::~FSPhysicalSystem()
  {
  }

  /**
   * @copydoc PhysicalSystem::internalTickCallback
   */
  void FSPhysicalSystem::internalTickCallback(btScalar timestep)
  {
    int numManifolds = m_world->getDispatcher()->getNumManifolds();
    for (int i = 0; i < numManifolds; i++)
    {
      btPersistentManifold *contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);

      const btCollisionObject *obA = contactManifold->getBody0();
      const btCollisionObject *obB = contactManifold->getBody1();

      const btCollisionObject *mr = m_aircraft->mainRotorBody();
      const btCollisionObject *tr = m_aircraft->tailRotorBody();
      const btCollisionObject *mb = m_aircraft->mainBody();

      bool rotorCanColl = ((obA == mr || obA == tr) && obB != mb) || ((obB == mr || obB == tr) && obA != mb);

      if (rotorCanColl)
      {
        int numContacts = contactManifold->getNumContacts();
        for (int j = 0; j < numContacts; j++)
        {
          btManifoldPoint &pt = contactManifold->getContactPoint(j);
          if (pt.getDistance() < 0.0f)
          {
            m_game->messageQueue().push(std::make_pair(Subsystem::GAME_LOGIC, "aircraft:reset"));
            break;
          }
        }
      }
    }
  }

  /**
   * @brief Sets the active aircraft.
   * @param Active aircraft
   */
  void FSPhysicalSystem::setActiveAircraft(Aircraft *aircraft)
  {
    if (m_aircraft != nullptr)
      m_aircraft->removeFromSystem(this);

    m_aircraft = aircraft;
    m_aircraft->addToSystem(this);
  }

  /**
   * @brief Sets the active terrain.
   * @param terrain Active terrain
   */
  void FSPhysicalSystem::setActiveTerrain(Terrain *terrain)
  {
    if (m_terrain != nullptr)
      m_terrain->removeFromSystem(this);

    m_terrain = terrain;
    m_terrain->addToSystem(this);
  }
}
}
