/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_GRAPHICS_HEIGHTMAPMESH_H_
#define _ENGINE_GRAPHICS_HEIGHTMAPMESH_H_

#include "Mesh.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @class HeightmapMesh
   * @brief TODO
   * @author Dan Nixon
   */
  class HeightmapMesh : public Mesh
  {
  public:
    HeightmapMesh(size_t dimX, size_t dimY, float sizeX, float sizeY);
    virtual ~HeightmapMesh();

    void setHeight(size_t x, size_t y, float height, bool buffer = false);
    void setHeight(float *height);

    Engine::Maths::Vector3 &vertexPosition(size_t x, size_t y);

  private:
    size_t m_widthSteps;
    size_t m_depthSteps;
  };
}
}

#endif
