/**
 * @file
 * @author Dan Nixon
 */

#include "LineMesh.h"

#include <Engine_Maths/Vector3.h>

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Create a new line mesh.
   * @param from Starting point
   * @param to Finishing point
   */
  LineMesh::LineMesh(const Vector3 &from, const Vector3 &to)
  {
    m_type = GL_LINES;
    m_numVertices = 2;

    m_vertices = new Vector3[m_numVertices];

    m_textureCoords = new Vector2[m_numVertices];
    m_textureCoords[0] = Vector2(1.0f, 1.0f);
    m_textureCoords[1] = Vector2(0.0f, 1.0f);

    m_colours = new Colour[m_numVertices];
    m_colours[0] = Colour(1.0f, 0.0f, 0.0f, 1.0f);
    m_colours[1] = Colour(1.0f, 0.0f, 0.0f, 1.0f);

    updateMesh(from, to);
  }

  LineMesh::~LineMesh()
  {
  }

  /**
   * @brief Sets starting point of the line.
   * @param from Starting point
   */
  void LineMesh::setFrom(const Vector3 &from)
  {
    updateMesh(from, m_vertices[1]);
  }

  /**
   * @brief Sets finishing point of the line.
   * @param to Finishing point
   */
  void LineMesh::setTo(const Vector3 &to)
  {
    updateMesh(m_vertices[0], to);
  }

  /**
   * @brief Updates the vertices of the mesh.
   * @param from Starting point
   * @param to Finishing point
   */
  void LineMesh::updateMesh(const Vector3 &from, const Vector3 &to)
  {
    m_vertices[0] = from;
    m_vertices[1] = to;

    bufferData();
  }
}
}
