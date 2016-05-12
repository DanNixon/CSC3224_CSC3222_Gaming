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
    static void CreateDistribution(Engine::Utility::Random &rand, float *bins, size_t nBins, size_t nIters);

  public:
    TerrainPeak(Engine::IO::KVNode &node);
    virtual ~TerrainPeak();

    void calculate(float *out, size_t dimX, size_t dimY) const;

  private:
    std::string m_xFunction; //!< Random function describing X distribution
    std::string m_yFunction; //!< Random function describing Y distribution
    size_t m_xSamples;       //!< Number of samples in X distribution
    size_t m_ySamples;       //!< Number of samples in Y distribution
    float m_factor;          //!< Scale factor
  };
}
}

#endif
