/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "TerrainPeak.h"

#include <Engine_Logging/Logger.h>

using namespace Engine::IO;
using namespace Engine::Utility;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace GameDev
{
namespace FlightSim
{
  /**
   * @brief Populates the distribution.
   * @param rand Random number function
   * @param bins Pointer to distribution bins
   * @param nBins NUmber of bins in distribution
   * @param nIters Number of sampes
   */
  void TerrainPeak::CreateDistribution(Random &rand, float *bins, size_t nBins, size_t nIters)
  {
    for (size_t i = 0; i < nIters;)
    {
      size_t binIdx = (size_t)rand();
      if (binIdx >= 0 && binIdx < nBins)
      {
        bins[binIdx]++;
        i++;
      }
    }
  }

  /**
   * @brief Create a new peak generator.
   * @param node Key-value node containing parameters
   */
  TerrainPeak::TerrainPeak(KVNode &node)
  {
    m_xFunction = "function=" + node.keyString("x_function");
    m_yFunction = "function=" + node.keyString("y_function");
    m_xSamples = node.keyUnsignedLong("x_samples");
    m_ySamples = node.keyUnsignedLong("y_samples");
    m_factor = node.keyFloat("factor");
  }

  TerrainPeak::~TerrainPeak()
  {
  }

  /**
   * @brief Calculates the new terrain shape inclusive of this peak.
   * @param out Pointer to existing terrain height data
   * @param dimX Terain dimensions in X axis
   * @param dimY Terrain dimensions in Y axis
   */
  void TerrainPeak::calculate(float *out, size_t dimX, size_t dimY) const
  {
    // Calculate X distribution
    float *distributionX = new float[dimX];
    std::fill(distributionX, distributionX + dimX, 0.0f);
    Random xRand(m_xFunction);
    CreateDistribution(xRand, distributionX, dimX, m_xSamples);

    // Calculate Y distribution
    float *distributionY = new float[dimY];
    std::fill(distributionY, distributionY + dimY, 0.0f);
    Random yRand(m_yFunction);
    CreateDistribution(yRand, distributionY, dimY, m_ySamples);

    float factor = m_factor / (m_xSamples + m_ySamples);

    // Iterate over grid
    for (size_t i = 0; i < dimX; i++)
    {
      for (size_t j = 0; j < dimY; j++)
      {
        out[i * dimY + j] += factor * distributionX[i] * distributionY[j];
      }
    }

    delete[] distributionX;
    delete[] distributionY;
  }
}
}
