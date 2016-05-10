/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_FSPHYSICALSYSTEM_H_
#define _GAMEDEV_FLIGHTSIM_FSPHYSICALSYSTEM_H_

#include <Engine_Physics/PhysicalSystem.h>

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class FSPhysicalSystem
   * @brief Flight simulator game.
   * @author Dan Nixon
   */
  class FSPhysicalSystem : public Engine::Physics::PhysicalSystem
  {
  public:
    FSPhysicalSystem(float targetTimeStep, float maxPossibleTimeStep, float worldScale = 100.0f);
    virtual ~FSPhysicalSystem();

    virtual void internalTickCallback(btScalar timestep);
  };
}
}

#endif
