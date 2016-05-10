/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "FSPhysicalSystem.h"

#include <sstream>

using namespace Engine::Physics;

namespace GameDev
{
namespace FlightSim
{
  FSPhysicalSystem::FSPhysicalSystem(float targetTimeStep, float maxPossibleTimeStep, float worldScale)
      : PhysicalSystem(targetTimeStep, maxPossibleTimeStep, worldScale)
  {
  }

  FSPhysicalSystem::~FSPhysicalSystem()
  {
  }

  void FSPhysicalSystem::internalTickCallback(btScalar timestep)
  {
    int numManifolds = m_world->getDispatcher()->getNumManifolds();
    for (int i = 0; i < numManifolds; i++)
    {
      btPersistentManifold *contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);
      auto obA = contactManifold->getBody0();
      auto obB = contactManifold->getBody1();

      int numContacts = contactManifold->getNumContacts();
      for (int j = 0; j < numContacts; j++)
      {
        btManifoldPoint &pt = contactManifold->getContactPoint(j);
        if (pt.getDistance() < 0.f)
        {
          const btVector3 &ptA = pt.getPositionWorldOnA();
          const btVector3 &ptB = pt.getPositionWorldOnB();
          const btVector3 &normalOnB = pt.m_normalWorldOnB;

          std::cout << "coll" << std::endl;
        }
      }
    }
  }
}
}
