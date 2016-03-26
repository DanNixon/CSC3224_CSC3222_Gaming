/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_RectangleMeshMESH_H_
#define _ENGINE_GRAPHICS_RectangleMeshMESH_H_

#include "Mesh.h"

#include <Vector2.h>

#include "Alignment.h"

namespace Engine
{
namespace Graphics
{
  /**
   * @class RectangleMesh
   * @brief A mesh containing a rectangle.
   * @author Dan Nixon
   */
  class RectangleMesh : public Mesh
  {
  public:
    RectangleMesh(const Engine::Maths::Vector2 &dimensions, Alignment_bitset alignment = Alignment_bitset());
    virtual ~RectangleMesh();

    /**
     * @brief Gets the dimensions of the rectangle.
     * @return Dimensions
     * @see RectangleMesh::setDimensions
     */
    inline Engine::Maths::Vector2 dimensions() const
    {
      return m_dimensions;
    }

    void setDimensions(const Engine::Maths::Vector2 &dimensions);

    /**
     * @brief Gets the alignment of the rectangle.
     * @return Alignment options
     * @see RectangleMesh::setAlignment
     */
    inline Alignment_bitset alignment() const
    {
      return m_alignment;
    }

    void setAlignment(const Alignment_bitset &alignment);

  private:
    void resize();

    Engine::Maths::Vector2 m_dimensions; //!< DImensions of the rectangle
    Alignment_bitset m_alignment;        //!< Alignment from the position origin
  };
}
}

#endif
