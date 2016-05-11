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
    TerrainPeak(Engine::IO::KVNode &node)
    {
      m_centreX = node.keyUnsignedLong("centre_x");
      m_centreY = node.keyUnsignedLong("centre_y");
      m_function = node.keyString("function");
      m_factor = node.keyFloat("factor");
    }

    virtual ~TerrainPeak()
    {
    }

    size_t centreX() const
    {
      return m_centreX;
    }

    size_t centreY() const
    {
      return m_centreY;
    }

    std::string function() const
    {
      return m_function;
    }

    float factor() const
    {
      return m_factor;
    }

    void calculate(float *out) const
    {
      // TODO
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
