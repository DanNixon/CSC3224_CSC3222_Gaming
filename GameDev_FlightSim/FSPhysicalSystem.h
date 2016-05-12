/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_FSPHYSICALSYSTEM_H_
#define _GAMEDEV_FLIGHTSIM_FSPHYSICALSYSTEM_H_

#include <Engine_Physics/PhysicalSystem.h>

#include "Aircraft.h"
#include "Terrain.h"

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class FSPhysicalSystem
   * @brief Physical system specific to running the flight simulator game physics.
   * @author Dan Nixon
   */
  class FSPhysicalSystem : public Engine::Physics::PhysicalSystem
  {
  public:
    FSPhysicalSystem(float targetTimeStep, float maxPossibleTimeStep, float worldScale, Engine::Common::Game *game);
    virtual ~FSPhysicalSystem();

    virtual void internalTickCallback(btScalar timestep);

    void setActiveAircraft(Aircraft *aircraft = nullptr);
    void setActiveTerrain(Terrain *terrain = nullptr);

  private:
    Engine::Common::Game *m_game; //!< Game in use

    Aircraft *m_aircraft; //!< Active aircraft
    Terrain *m_terrain;   //!< Active terrain
  };
}
}

#endif
