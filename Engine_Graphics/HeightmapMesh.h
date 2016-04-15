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
    HeightmapMesh(unsigned long dimX, unsigned long dimY, float sizeX, float sizeY);
    virtual ~HeightmapMesh();

  private:
    unsigned long m_widthSteps;
    unsigned long m_depthSteps;
  };
}
}

#endif
