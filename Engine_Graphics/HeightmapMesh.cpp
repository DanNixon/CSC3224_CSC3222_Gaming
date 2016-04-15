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
   *
   * Index generation was adapted from here:
   * http://www.chadvernon.com/blog/resources/directx9/terrain-generation-with-a-heightmap
   */
  HeightmapMesh::HeightmapMesh(unsigned long widthSteps, unsigned long depthSteps, float width, float depth)
      : m_widthSteps(widthSteps)
      , m_depthSteps(depthSteps)
  {
    m_type = GL_TRIANGLE_STRIP;

    m_numVertices = m_widthSteps * m_depthSteps;
    m_vertices = new Vector3[m_numVertices];
    m_textureCoords = new Vector2[m_numVertices];
    m_colours = new Colour[m_numVertices];

    m_numIndices = (m_widthSteps * 2) * (m_depthSteps - 1) + (m_depthSteps - 2);
    m_indices = new GLuint[m_numIndices];

    // Half the plane size
    Vector3 halfSize(width / 2.0f, 0.0f, depth / 2.0f);

    // Space between each adjacent vertex in each axis
    const float deltaRow = depth / (float)(m_depthSteps - 1);
    const float deltaCol = width / (float)(m_widthSteps - 1);

    // Generate vertices
    unsigned int idx = 0;
    for (unsigned int row = 0; row < m_depthSteps; row++)
    {
      for (unsigned int col = 0; col < m_widthSteps; col++)
      {
        // Positional coordinates
        float x = (float)col * deltaRow;
        float z = (float)row * deltaCol;

        // Texture coordinates
        float u = (float)col / (float)m_widthSteps;
        float v = (float)row / (float)m_depthSteps;

        m_vertices[idx] = Vector3(x, 0.0f, z) - halfSize;
        m_textureCoords[idx] = Vector2(u, v);
        m_colours[idx] = Colour(u, v, 0.0f, 1.0f);

        idx++;
      }
    }
    
    // Generate indices
    int index = 0;
    for (int z = 0; z < depthSteps - 1; z++)
    {
      int x;

      // Even row (left to right)
      if (z % 2 == 0)
      {
        for (x = 0; x < widthSteps; x++)
        {
          m_indices[index++] = x + (z * widthSteps);
          m_indices[index++] = x + (z * widthSteps) + widthSteps;
        }

        // Degenerate triangle at end of non-last row
        if (z != depthSteps - 2)
          m_indices[index++] = --x + (z * widthSteps);
      }
      // Odd row (right to left)
      else
      {
        for (x = widthSteps - 1; x >= 0; x--)
        {
          m_indices[index++] = x + (z * widthSteps);
          m_indices[index++] = x + (z * widthSteps) + widthSteps;
        }

        // Degenerate triangle at end of non-last row
        if (z != depthSteps - 2)
          m_indices[index++] = ++x + (z * widthSteps);
      }
    }

    bufferData();
  }

  HeightmapMesh::~HeightmapMesh()
  {
  }
}
}
