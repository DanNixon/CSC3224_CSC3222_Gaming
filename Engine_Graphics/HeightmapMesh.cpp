/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "HeightmapMesh.h"

#include <Engine_Maths/Vector3.h>

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new heightmap mesh.
   * @param widthSteps Number of vertices in the height map grid in the X axis
   * @param depthSteps Number of vertices in the height map grid in the Z axis
   * @param width Length of the height map in the X axis
   * @param depth Length of the height map in the Z axis
   *
   * Index generation was adapted from here:
   * http://www.chadvernon.com/blog/resources/directx9/terrain-generation-with-a-heightmap
   */
  HeightmapMesh::HeightmapMesh(size_t widthSteps, size_t depthSteps, float width, float depth)
      : m_widthSteps(widthSteps)
      , m_depthSteps(depthSteps)
  {
    // Invert for coordinate system
    depth = -depth;

    // m_type = GL_TRIANGLE_STRIP;
    m_type = GL_LINE_STRIP;

    m_numVertices = m_widthSteps * m_depthSteps;
    m_vertices = new Vector3[m_numVertices];
    m_textureCoords = new Vector2[m_numVertices];
    m_colours = new Colour[m_numVertices];

    m_numIndices = (m_widthSteps * 2) * (m_depthSteps - 1) + (m_depthSteps - 2);
    m_indices = new GLuint[m_numIndices];

    // Half the plane size
    Vector3 halfSize(width / 2.0f, 0.0f, depth / 2.0f);

    // Space between each adjacent vertex in each axis
    m_deltaCol = width / (float)(m_widthSteps - 1);
    m_deltaRow = depth / (float)(m_depthSteps - 1);

    // Generate vertices
    size_t idx = 0;
    for (size_t col = 0; col < m_widthSteps; col++)
    {
      for (size_t row = 0; row < m_depthSteps; row++)
      {
        // Positional coordinates
        float x = (float)col * m_deltaCol;
        float z = (float)row * m_deltaRow;

        // Texture coordinates
        float u = (float)col / (float)m_widthSteps;
        float v = (float)row / (float)m_depthSteps;

        auto thisvect = Vector3(x, 0.0f, z) - halfSize;

        m_vertices[idx] = Vector3(x, 0.0f, z) - halfSize;
        m_textureCoords[idx] = Vector2(u, v);
        m_colours[idx] = Colour(u, v, 0.0f, 1.0f);

        idx++;
      }
    }

    // Generate indices
    int index = 0;
    for (size_t z = 0; z < depthSteps - 1; z++)
    {
      int x;

      // Even row (left to right)
      if (z % 2 == 0)
      {
        for (x = 0; x < widthSteps; x++)
        {
          m_indices[index++] = (GLuint)(x + (z * widthSteps));
          m_indices[index++] = (GLuint)(x + (z * widthSteps) + widthSteps);
        }

        // Degenerate triangle at end of non-last row
        if (z != depthSteps - 2)
          m_indices[index++] = (GLuint)(--x + (z * widthSteps));
      }
      // Odd row (right to left)
      else
      {
        for (x = widthSteps - 1; x >= 0; x--)
        {
          m_indices[index++] = (GLuint)(x + (z * widthSteps));
          m_indices[index++] = (GLuint)(x + (z * widthSteps) + widthSteps);
        }

        // Degenerate triangle at end of non-last row
        if (z != depthSteps - 2)
          m_indices[index++] = (GLuint)(++x + (z * widthSteps));
      }
    }

    bufferData();
  }

  HeightmapMesh::~HeightmapMesh()
  {
  }

  /**
   * @brief Sets the height of a given vertex in the height map.
   * @param row Row index
   * @param col Column index
   * @param height New height
   * @param buffer Set to true to output VBOs
   */
  void HeightmapMesh::setHeight(size_t row, size_t col, float height, bool buffer)
  {
    vertexPosition(row, col)[1] = height;

    // Update buffers
    if (buffer)
      bufferData();
  }

  /**
   * @brief Sets the height of each vertex in the height map.
   * @param height Pointer to array of height data (must be equal in length to
   *               vertex array)
   *
   * Buffers are updated.
   */
  void HeightmapMesh::setHeight(float *height)
  {
    // Update y coordinates
    for (size_t i = 0; i < m_numVertices; i++)
      m_vertices[i][1] = height[i];

    // Update buffers
    bufferData();
  }

  /**
   * @brief Returns a reference to the position vector of a given vertex in
   *        the height map.
   * @param row Row index
   * @param col Column index
   * @return Reference to vertex position
   */
  Engine::Maths::Vector3 &HeightmapMesh::vertexPosition(size_t row, size_t col)
  {
    size_t idx = (col * m_depthSteps) + row;
    return m_vertices[idx];
  }
}
}
