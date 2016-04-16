/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Heightmap.h"

using namespace Engine::Graphics;

namespace Engine
{
namespace Physics
{
  Heightmap::Heightmap()
      : m_shape(nullptr)
  {
  }

  Heightmap::~Heightmap()
  {
  }

  void Heightmap::populate(HeightmapMesh *heightmap)
  {
    size_t widthSteps = heightmap->widthSteps();
    size_t depthSteps = heightmap->depthSteps();

    size_t numPoints = widthSteps * depthSteps;

    float *data = new float[numPoints];
    float minHeight = std::numeric_limits<float>::max();
    float maxHeight = std::numeric_limits<float>::min();
    for (size_t i = 0; i < numPoints; i++)
    {
      float height = heightmap->vertices()[i].y();
      data[i] = height;
      minHeight = std::min(minHeight, height);
      maxHeight = std::max(maxHeight, height);
    }

    minHeight = -50.0f;
    maxHeight = 50.0f;

    m_shape =
        new btHeightfieldTerrainShape(widthSteps, depthSteps, data, 1.0f, minHeight, maxHeight, 1, PHY_FLOAT, false);

    btVector3 localScale(heightmap->deltaCol(), 1.0f, -heightmap->deltaRow());
    m_shape->setLocalScaling(localScale);
  }
}
}
