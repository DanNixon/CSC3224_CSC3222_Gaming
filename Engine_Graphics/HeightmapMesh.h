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
   * @brief Mesh for drawing a height map plane.
   * @author Dan Nixon
   */
  class HeightmapMesh : public Mesh
  {
  public:
    HeightmapMesh(size_t widthSteps, size_t depthSteps, float width, float depth);
    virtual ~HeightmapMesh();

    /**
     * @brief Gets the number of vertices in the X axis.
     * @return Width vertex count
     */
    size_t widthSteps() const
    {
      return m_widthSteps;
    }

    /**
     * @brief Gets the number of vertices in the Z axis.
     * @return Depth vertex count
     */
    size_t depthSteps() const
    {
      return m_depthSteps;
    }

    /**
     * @brief Distance between adjacent nodes of the heightmap in the Z axis.
     * @return Row spacing
     */
    float deltaRow() const
    {
      return m_deltaRow;
    }

    /**
     * @brief Distance between adjacent nodes of the heightmap in the X axis.
     * @return Column spacing
     */
    float deltaCol() const
    {
      return m_deltaCol;
    }

    void setHeight(size_t row, size_t col, float height, bool buffer = false);
    void setHeight(float *height);

    Engine::Maths::Vector3 &vertexPosition(size_t row, size_t col);

  private:
    size_t m_widthSteps; //!< Number of vertices along X axis
    size_t m_depthSteps; //!< Number of vertices along Z axis
    float m_deltaRow;    //!< Row spacing
    float m_deltaCol;    //!< Column spacing
  };
}
}

#endif
