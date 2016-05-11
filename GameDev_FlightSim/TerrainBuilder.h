/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_TERRAINBUILDER_H_
#define _GAMEDEV_FLIGHTSIM_TERRAINBUILDER_H_

#include <Engine_IO/INIKeyValueStore.h>
#include <Engine_ResourceManagment/IMemoryManaged.h>

#include "Terrain.h"
#include "TerrainPeak.h"

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class TerrainBuilder
   * @brief Class containing functionality for building a terrain.
   * @author Dan Nixon
   */
  class TerrainBuilder : public Engine::ResourceManagment::IMemoryManaged, public Engine::IO::INIKeyValueStore
  {
  public:
    TerrainBuilder(const std::string &name, const std::string &resourceRoot);
    virtual ~TerrainBuilder();

    std::string metadataFilename() const;
    void loadMetadata();

    inline std::string name() const
    {
      return m_name;
    }

    inline std::string displayName() const
    {
      return m_displayName;
    }

    inline float width() const
    {
      return m_width;
    }

    inline float depth() const
    {
      return m_depth;
    }

    void generate(Terrain *terrain);

  private:
    std::string m_resourceRoot; //!< Path to the root of the resources directory

    std::string m_name;
    std::string m_displayName;

    float m_width;
    float m_depth;

    size_t m_resolutionX;
    size_t m_resolutionY;

    float m_baselineAltitude;

    std::vector<TerrainPeak> m_peaks;
  };
}
}

#endif
