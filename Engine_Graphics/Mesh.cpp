/**
 * @file
 * @author Dan Nixon
 */

#include "Mesh.h"

#include <VectorOperations.h>
#include <math_common.h>

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Gets the upper and lower bounds of the vertices of a mesh.
   * @param m Mesh to get bounds for
   * @return Pair containing upper and lower bounding vertices
   */
  std::pair<Vector3, Vector3> Mesh::GetBoundingBox(Mesh *m)
  {
    const float maxFloat = std::numeric_limits<float>::max();
    const float minFloat = std::numeric_limits<float>::min();

    Vector3 min(maxFloat, maxFloat, maxFloat);
    Vector3 max(minFloat, minFloat, minFloat);

    for (size_t i = 0; i < m->m_numVertices; i++)
    {
      const Vector3 &v = m->m_vertices[i];

      for (int j = 0; j < 3; j++)
      {
        if (v[j] < min[j])
          min[j] = v[j];
        else if (v[j] > max[j])
          max[j] = v[j];
      }
    }

    return std::make_pair(min, max);
  }

  /**
   * @brief Creates a new empty mesh.
   */
  Mesh::Mesh()
      : m_numIndices(0)
      , m_type(GL_TRIANGLES)
      , m_vertices(NULL)
      , m_colours(NULL)
      , m_textureCoords(NULL)
      , m_normals(NULL)
      , m_tangents(NULL)
      , m_indices(NULL)
  {
    glGenVertexArrays(1, &m_arrayObject);

    for (int i = 0; i < MAX_BUFFER; ++i)
      m_bufferObject[i] = 0;
  }

  Mesh::~Mesh(void)
  {
    glDeleteVertexArrays(1, &m_arrayObject);
    glDeleteBuffers(MAX_BUFFER, m_bufferObject);

    delete[] m_vertices;
    delete[] m_colours;
    delete[] m_textureCoords;
    delete[] m_normals;
    delete[] m_tangents;
    delete[] m_indices;
  }

  /**
   * @brief Draws mesh.
   */
  void Mesh::draw()
  {
    glBindVertexArray(m_arrayObject);

    if (m_bufferObject[INDEX_BUFFER])
      glDrawElements(m_type, m_numIndices, GL_UNSIGNED_INT, 0);
    else
      glDrawArrays(m_type, 0, m_numVertices);

    glBindVertexArray(0);
  }

  /**
   * @brief Sets all vertix colours in the mesh to a solid colour.
   * @param col Colour to set
   */
  void Mesh::setStaticColour(const Vector4 &col)
  {
    if (m_colours != NULL)
    {
      for (size_t i = 0; i < m_numVertices; i++)
        m_colours[i] = col;
    }

    bufferData();
  }

  /**
   * @brief Generates normals for each vertex.
   * @return True if normals were generated
   *
   * Requires that faces are triangles.
   */
  bool Mesh::generateNormals()
  {
    if (m_type != GL_TRIANGLES)
      return false;

    if (!m_normals)
      m_normals = new Vector3[m_numVertices];

    for (unsigned int i = 0; i < m_numVertices; i += 3)
    {
      Vector3 &a = m_vertices[i];
      Vector3 &b = m_vertices[i + 1];
      Vector3 &c = m_vertices[i + 2];

      Vector3 normal = Vector3::cross(b - a, c - a);
      VectorOperations::Normalise(normal);

      m_normals[i] = normal;
      m_normals[i + 1] = normal;
      m_normals[i + 2] = normal;
    }

    return true;
  }

  /**
   * @brief Buffers all VBO data into graphics memory.
   *
   * Required before drawing.
   */
  void Mesh::bufferData()
  {
    glBindVertexArray(m_arrayObject);

    glGenBuffers(1, &m_bufferObject[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector3), m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_BUFFER);

    /* Buffer texture data */
    if (m_textureCoords)
    {
      glGenBuffers(1, &m_bufferObject[TEXTURE_BUFFER]);
      glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[TEXTURE_BUFFER]);
      glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector2), m_textureCoords, GL_STATIC_DRAW);
      glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(TEXTURE_BUFFER);
    }

    /* Buffer colour data */
    if (m_colours)
    {
      glGenBuffers(1, &m_bufferObject[COLOUR_BUFFER]);
      glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[COLOUR_BUFFER]);
      glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector4), m_colours, GL_STATIC_DRAW);
      glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(COLOUR_BUFFER);
    }

    /* Buffer index data */
    if (m_indices)
    {
      glGenBuffers(1, &m_bufferObject[INDEX_BUFFER]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferObject[INDEX_BUFFER]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLuint), m_indices, GL_STATIC_DRAW);
    }

    /* Buffer normals data */
    if (m_normals)
    {
      glGenBuffers(1, &m_bufferObject[NORMAL_BUFFER]);
      glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[NORMAL_BUFFER]);
      glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector3), m_normals, GL_STATIC_DRAW);

      glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(NORMAL_BUFFER);
    }

    glBindVertexArray(0);
  }

  /**
   * @brief Generates a 2D filled circle/disc.
   * @param radius Radius (default 1.0)
   * @param resolution Number of "slices" in angle
   * @return New mesh
   */
  Mesh *Mesh::GenerateDisc2D(float radius, int resolution)
  {
    Mesh *m = new Mesh();
    m->m_type = GL_TRIANGLE_FAN;

    m->m_numVertices = resolution + 2;
    m->m_vertices = new Vector3[m->m_numVertices];
    m->m_colours = new Vector4[m->m_numVertices];
    m->m_textureCoords = new Vector2[m->m_numVertices];

    const float deltaA = ((PI * 2) / resolution);

    // "Origin" vertex
    m->m_vertices[0] = Vector3(0.0f, 0.0f, 0.0f);
    m->m_colours[0] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    m->m_textureCoords[0] = Vector2(0.5f, 0.5f);

    for (int i = 1; i < resolution + 2; ++i)
    {
      const float a = i * deltaA;

      m->m_vertices[i] = Vector3(cos(a) * radius, sin(a) * radius, 0.0f);
      m->m_colours[i] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
      Vector2 v = Vector2(abs(cos(a)), abs(sin(a)));
      m->m_textureCoords[i] = v;
    }

    m->bufferData();
    return m;
  }

  /**
  * @brief Generates a 2D ring.
  * @param radiusOuter Outer radius
  * @param radiusInner Inner radius
  * @param resolution Number of "slices" in angle
  * @return Mesh containing 2D ring
  */
  Mesh *Mesh::GenerateRing2D(float radiusOuter, float radiusInner, int resolution)
  {
    Mesh *m = new Mesh();
    m->m_type = GL_TRIANGLE_STRIP;

    m->m_numVertices = (resolution + 2) * 2;
    m->m_vertices = new Vector3[m->m_numVertices];
    m->m_colours = new Vector4[m->m_numVertices];
    m->m_textureCoords = new Vector2[m->m_numVertices];

    const float deltaA = ((PI * 2) / resolution);
    const Vector4 c(1, 1, 1, 127);

    int n = 0;
    for (int i = 0; i < resolution + 2; i++)
    {
      const float a = i * deltaA;

      m->m_vertices[n] = Vector3(cos(a) * radiusOuter, sin(a) * radiusOuter, 0.0f);
      m->m_colours[n] = c;
      m->m_textureCoords[n] = Vector2(abs(cos(a)), abs(sin(a)));
      n++;

      m->m_vertices[n] = Vector3(cos(a) * radiusInner, sin(a) * radiusInner, 0.0f);
      m->m_colours[n] = c;
      m->m_textureCoords[n] = Vector2(abs(cos(a)), abs(sin(a)));
      n++;
    }

    m->bufferData();
    return m;
  }

  /**
   * @brief Loads a mesh from an Assimp mesh.
   * @param mesh Assimp mesh to load
   * @param material Material used on mesh
   * @return Mesh containing loaded model
   */
  Mesh *Mesh::LoadMesh(const struct aiMesh *mesh, const struct aiMaterial * material)
  {
    Mesh *m = new Mesh();
    m->m_type = GL_TRIANGLES;
    // m->m_type = GL_LINES;

    aiVector3D *vertices = mesh->mVertices;

    m->m_numVertices = mesh->mNumFaces * 3;
    m->m_vertices = new Vector3[m->m_numVertices];
    m->m_colours = new Vector4[m->m_numVertices];

    // Load vertices
    size_t idx = 0;
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
      const aiFace &face = mesh->mFaces[i];

      aiVector3D v;
      for (int j = 0; j < 3; j++)
      {
        if (face.mNumIndices > j)
          v = vertices[face.mIndices[j]];

        m->m_colours[idx] = Vector4(1, 1, 1, 1);
        m->m_vertices[idx++] = Vector3(v[0], v[1], v[2]);
      }
    }

    m->generateNormals();
    m->bufferData();

    return m;
  }
}
}
