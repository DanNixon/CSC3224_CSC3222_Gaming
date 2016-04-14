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
  HeightmapMesh::HeightmapMesh()
  {
    m_type = GL_LINES;
    m_numVertices = 2;

    m_vertices = new Vector3[m_numVertices];
    m_textureCoords = new Vector2[m_numVertices];
    m_colours = new Colour[m_numVertices];
  }

  HeightmapMesh::~HeightmapMesh()
  {
  }
}
}
