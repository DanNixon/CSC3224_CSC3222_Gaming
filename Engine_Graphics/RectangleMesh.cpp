/**
 * @file
 * @author Dan Nixon
 */

#include "RectangleMesh.h"

#include <Vector4.h>

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new rectangle mesh.
   * @param dimensions Dimensions of the rectangle
   * @param alignment Alignment of rectangle
   *
   * Rectangle is generated centered about the current position.
   */
  RectangleMesh::RectangleMesh(const Vector2 &dimensions, Alignment_bitset alignment)
      : m_dimensions(dimensions)
      , m_alignment(alignment)
  {
    m_type = GL_TRIANGLE_STRIP;
    m_numVertices = 4;

    m_vertices = new Vector3[m_numVertices];

    m_colours = new Colour[m_numVertices];
    m_colours[0] = Colour(1.0f, 1.0f, 1.0f, 1.0f);
    m_colours[1] = Colour(1.0f, 0.0f, 0.0f, 1.0f);
    m_colours[2] = Colour(0.0f, 1.0f, 0.0f, 1.0f);
    m_colours[3] = Colour(0.0f, 0.0f, 1.0f, 1.0f);

    m_textureCoords = new Vector2[m_numVertices];
    m_textureCoords[0] = Vector2(0, 0);
    m_textureCoords[1] = Vector2(1, 0);
    m_textureCoords[2] = Vector2(0, 1);
    m_textureCoords[3] = Vector2(1, 1);

    resize();
  }

  RectangleMesh::~RectangleMesh()
  {
  }

  void RectangleMesh::setDimensions(const Vector2 &dimensions)
  {
    m_dimensions = dimensions;
    resize();
  }

  void RectangleMesh::setAlignment(const Alignment_bitset &alignment)
  {
    m_alignment = alignment;
    resize();
  }

  /**
   * @brief Updates the vertices of the rectangle.
   */
  void RectangleMesh::resize()
  {
    Vector2 topRight = m_dimensions / 2;
    Vector2 bottomLeft = -topRight;

    if (m_alignment.test(Alignment::X_LEFT))
    {
      bottomLeft[0] += topRight.x();
      topRight[0] += topRight.x();
    }
    else if (m_alignment.test(Alignment::X_RIGHT))
    {
      bottomLeft[0] -= topRight.x();
      topRight[0] -= topRight.x();
    }

    if (m_alignment.test(Alignment::Y_BOTTOM))
    {
      bottomLeft[1] += topRight.y();
      topRight[1] += topRight.y();
    }
    else if (m_alignment.test(Alignment::Y_TOP))
    {
      bottomLeft[1] -= topRight.y();
      topRight[1] -= topRight.y();
    }

    m_vertices[0] = Vector3(bottomLeft.x(), topRight.y(), 0);
    m_vertices[1] = Vector3(topRight.x(), topRight.y(), 0);
    m_vertices[2] = Vector3(bottomLeft.x(), bottomLeft.y(), 0);
    m_vertices[3] = Vector3(topRight.x(), bottomLeft.y(), 0);

    bufferData();
  }
}
}
