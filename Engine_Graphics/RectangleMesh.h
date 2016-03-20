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

    inline Engine::Maths::Vector2 dimensions() const
    {
      return m_dimensions;
    }

    void setDimensions(const Engine::Maths::Vector2 &dimensions);

    inline Alignment_bitset alignment() const
    {
      return m_alignment;
    }

    void setAlignment(const Alignment_bitset &alignment);

  private:
    void resize();

    Engine::Maths::Vector2 m_dimensions;
    Alignment_bitset m_alignment;
  };
}
}

#endif
