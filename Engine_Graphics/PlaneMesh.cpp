/**
 * @file
 * @author Dan Nixon
 */

#include "PlaneMesh.h"

#include <Engine_Maths/Vector4.h>

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new plane mesh.
   * @param axis Axis to create plane in (x, y, or z)
   * @param size Size of the plane
   */
  PlaneMesh::PlaneMesh(char axis, float size)
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

    m_vertices = new Vector3[m_numVertices];
    switch (axis)
    {
    case 'x':
    case 'X':
      m_vertices[0] = Vector3(0.0f, -size, -size);
      m_vertices[1] = Vector3(0.0f, size, -size);
      m_vertices[2] = Vector3(0.0f, -size, size);
      m_vertices[3] = Vector3(0.0f, size, size);
      break;
    case 'y':
    case 'Y':
      m_vertices[0] = Vector3(-size, 0.0f, -size);
      m_vertices[1] = Vector3(size, 0.0f, -size);
      m_vertices[2] = Vector3(-size, 0.0f, size);
      m_vertices[3] = Vector3(size, 0.0f, size);
      break;
    case 'z':
    case 'Z':
      m_vertices[0] = Vector3(-size, -size, 0.0f);
      m_vertices[1] = Vector3(size, -size, 0.0f);
      m_vertices[2] = Vector3(-size, size, 0.0f);
      m_vertices[3] = Vector3(size, size, 0.0f);
      break;
    }

    m_boundingBox.resizeByPoint(m_vertices[0]);
    m_boundingBox.resizeByPoint(m_vertices[1]);
    m_boundingBox.resizeByPoint(m_vertices[2]);
    m_boundingBox.resizeByPoint(m_vertices[3]);

    bufferData();
  }

  PlaneMesh::~PlaneMesh()
  {
  }
}
}
