/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_TERRAINPEAK_H_
#define _GAMEDEV_FLIGHTSIM_TERRAINPEAK_H_

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class TerrainPeak
   * @brief Class containing information about a peak on a terrain.
   * @author Dan Nixon
   */
  class TerrainPeak
  {
  public:
    TerrainPeak()
    {
      // TODO
    }

    virtual ~TerrainPeak()
    {
    }

  private:
    size_t m_centreX;
    size_t m_centreY;
    std::string m_function;
    float m_factor;
  };
}
}

#endif
