/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_TERRAINBUILDER_H_
#define _GAMEDEV_FLIGHTSIM_TERRAINBUILDER_H_

#include <Engine_IO/INIKeyValueStore.h>

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class TerrainBuilder
   * @brief Class containing functionality for building a terrain.
   * @author Dan Nixon
   */
  class TerrainBuilder : public Engine::IO::INIKeyValueStore
  {
  public:
    TerrainBuilder();
    virtual ~TerrainBuilder();

  };
}
}

#endif
