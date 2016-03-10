/**
 * @file
 * @author Dan Nixon
 */

#include "LineMesh.h"

#include <Vector3.h>

using namespace Engine::Maths;

namespace Engine
{
  namespace Graphics
  {
    LineMesh::LineMesh(const Vector3 &from, const Vector3 &to)
    {
      m_type = GL_LINES;
      m_numVertices = 2;

      m_vertices = new Vector3[m_numVertices];

      m_textureCoords = new Vector2[m_numVertices];
      m_textureCoords[0] = Vector2(1.0f, 1.0f);
      m_textureCoords[1] = Vector2(0.0f, 1.0f);

      m_colours = new Vector4[m_numVertices];
      m_colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
      m_colours[1] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

      updateMesh(from, to);
    }

    LineMesh::~LineMesh()
    {
    }

    void LineMesh::setFrom(const Vector3 &from)
    {
      updateMesh(from, m_vertices[1]);
    }

    void LineMesh::setTo(const Vector3 &to)
    {
      updateMesh(m_vertices[0], to);
    }

    void LineMesh::updateMesh(const Vector3 &from, const Vector3 &to)
    {
      m_vertices[0] = from;
      m_vertices[1] = to;

      bufferData();
    }
  }
}