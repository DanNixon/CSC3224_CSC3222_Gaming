/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_TERRAINPEAK_H_
#define _GAMEDEV_FLIGHTSIM_TERRAINPEAK_H_

#include <Engine_IO/KVNode.h>
#include <Engine_Utility/Random.h>

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
  private:
    static void DoIterations(Engine::Utility::Random &rand, float *bins, size_t nBins, size_t nIters);

  public:
    TerrainPeak(Engine::IO::KVNode &node);
    virtual ~TerrainPeak();

    void calculate(float *out, size_t dimX, size_t dimY) const;

  private:
    std::string m_xFunction;
    std::string m_yFunction;
    size_t m_xSamples;
    size_t m_ySamples;
    float m_factor;
  };
}
}

#endif
