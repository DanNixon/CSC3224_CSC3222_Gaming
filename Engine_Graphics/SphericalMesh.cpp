/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "SphericalMesh.h"

#include <Engine_Maths/Vector3.h>

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Create a new spherical mesh.
   * @param radius Radius
   * @param resolution Number of steps in each axis
   */
  SphericalMesh::SphericalMesh(float radius, size_t resolution)
      : m_resolution(resolution)
      , m_deltaTheta(static_cast<float>(M_PI / resolution))
      , m_deltaPhi(static_cast<float>((M_PI * 2.0f) / resolution))
  {
    m_type = GL_TRIANGLE_STRIP;
    m_numVertices = static_cast<size_t>(m_resolution) * static_cast<size_t>(m_resolution) * 2;

    m_vertices = new Vector3[m_numVertices];
    m_colours = new Colour[m_numVertices];
    m_textureCoords = new Vector2[m_numVertices];

    const float texEpsilon = 1.0f / m_resolution;

    // Generate colors and texture coordinates
    int n = 0;
    for (int i = 0; i < m_resolution; i++)
    {
      const float u1 = i * texEpsilon;
      const float u2 = (i + 1) * texEpsilon;

      for (int j = 0; j < m_resolution; j++)
      {
        const float v = j * texEpsilon;

        m_colours[n] = Colour();
        m_textureCoords[n] = Vector2(u1, v);
        n++;

        m_colours[n] = Colour();
        m_textureCoords[n] = Vector2(u2, v);
        n++;
      }
    }

    updateMesh(radius);
  }

  SphericalMesh::~SphericalMesh()
  {
  }

  /**
   * @brief Sets the radius of the sphere and re-calculates vertex positions.
   * @param radius Radius
   */
  void SphericalMesh::setRadius(float radius)
  {
    updateMesh(radius);
  }

  /**
   * @brief Updates the vertices of the mesh.
   * @param radius Radius
   */
  void SphericalMesh::updateMesh(float radius)
  {
    m_radius = radius;
    m_boundingBox.reset();

    // Generate vertex positions
    int n = 0;
    for (int i = 0; i < m_resolution; i++)
    {
      const float theta1 = i * m_deltaTheta;
      const float theta2 = (i + 1) * m_deltaTheta;

      for (int j = 0; j < m_resolution; j++)
      {
        const float phi = j * m_deltaPhi;

        m_vertices[n] =
            Vector3(cos(theta1) * sin(phi) * m_radius, sin(theta1) * sin(phi) * m_radius, cos(phi) * m_radius);
        m_boundingBox.resizeByPoint(m_vertices[n]);
        n++;

        m_vertices[n] =
            Vector3(cos(theta2) * sin(phi) * m_radius, sin(theta2) * sin(phi) * m_radius, cos(phi) * m_radius);
        m_boundingBox.resizeByPoint(m_vertices[n]);
        n++;
      }
    }

    bufferData();
  }
}
}
