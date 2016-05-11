/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "TerrainBuilder.h"

#include <fstream>

#include <Engine_Logging/Logger.h>

using namespace Engine::Maths;

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace GameDev
{
namespace FlightSim
{
  TerrainBuilder::TerrainBuilder(const std::string &name, const std::string &resourceRoot)
      : m_name(name)
      , m_resourceRoot(resourceRoot)
  {
  }

  TerrainBuilder::~TerrainBuilder()
  {
  }

  std::string TerrainBuilder::metadataFilename() const
  {
    std::stringstream str;
    str << m_resourceRoot << m_name;
    return str.str();
  }

  void TerrainBuilder::loadMetadata()
  {
    // Load data
    std::ifstream file(metadataFilename());
    load(file);

    // Skip loading if this terrain is not enabled
    if (!m_rootKVNode.child("general").keyBool("enabled"))
      return;

    // Parse member data
    m_displayName = m_rootKVNode.child("general").keyString("name");

    m_width = m_rootKVNode.child("dimensions").keyFloat("width_m") * 100.0f;
    m_depth = m_rootKVNode.child("dimensions").keyFloat("depth_m") * 100.0f;

    m_resolutionX = m_rootKVNode.child("dimensions").keyUnsignedLong("resolution_x");
    m_resolutionY = m_rootKVNode.child("dimensions").keyUnsignedLong("resolution_y");

    m_baselineAltitude = m_rootKVNode.child("basic").keyFloat("baseline_altitude");

    // Parse peaks
    size_t numPeaks = m_rootKVNode.child("basic").keyUnsignedLong("peaks_count");
    m_peaks.reserve(numPeaks);

    for (size_t i = 0; i < numPeaks; i++)
      m_peaks.push_back(TerrainPeak(m_rootKVNode.child("peak_" + std::to_string(i))));
  }

  void TerrainBuilder::generate(Terrain *terrain)
  {
    // Create height data array
    size_t dataSize = m_resolutionX * m_resolutionY;
    float *heightData = new float[dataSize];

    // Set baseline altitude
    std::fill(heightData, heightData + dataSize, m_baselineAltitude);

    // Add peaks
    for (auto it = m_peaks.begin(); it != m_peaks.end(); ++it)
    {
      // TODO
    }

    // Init terrain
    terrain->init(m_width, m_depth, m_resolutionX, m_resolutionY, heightData);
    delete[] heightData;
  }
}
}
