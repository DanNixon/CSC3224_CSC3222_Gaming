/**
 * @file
 * @author Dan Nixon
 */

#include "Mesh.h"

#include "math_common.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

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
      normal.normalise();

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
    glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector3), m_vertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_BUFFER);

    /* Buffer texture data */
    if (m_textureCoords)
    {
      glGenBuffers(1, &m_bufferObject[TEXTURE_BUFFER]);
      glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[TEXTURE_BUFFER]);
      glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector2),
                   m_textureCoords, GL_STATIC_DRAW);
      glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(TEXTURE_BUFFER);
    }

    /* Buffer colour data */
    if (m_colours)
    {
      glGenBuffers(1, &m_bufferObject[COLOUR_BUFFER]);
      glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[COLOUR_BUFFER]);
      glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector4), m_colours,
                   GL_STATIC_DRAW);
      glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(COLOUR_BUFFER);
    }

    /* Buffer index data */
    if (m_indices)
    {
      glGenBuffers(1, &m_bufferObject[INDEX_BUFFER]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferObject[INDEX_BUFFER]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLuint),
                   m_indices, GL_STATIC_DRAW);
    }

    /* Buffer normals data */
    if (m_normals)
    {
      glGenBuffers(1, &m_bufferObject[NORMAL_BUFFER]);
      glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[NORMAL_BUFFER]);
      glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector3), m_normals,
                   GL_STATIC_DRAW);

      glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(NORMAL_BUFFER);
    }

    glBindVertexArray(0);
  }

  /**
   * @brief Creates a coloured triangle for demonstration.
   * @return Mesh containing triangle
   */
  Mesh *Mesh::GenerateTriangle()
  {
    Mesh *m = new Mesh();
    m->m_numVertices = 3;

    m->m_vertices = new Vector3[m->m_numVertices];
    m->m_vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
    m->m_vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
    m->m_vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);

    m->m_textureCoords = new Vector2[m->m_numVertices];
    m->m_textureCoords[0] = Vector2(0.5f, 0.0f);
    m->m_textureCoords[1] = Vector2(1.0f, 1.0f);
    m->m_textureCoords[2] = Vector2(0.0f, 1.0f);

    m->m_colours = new Vector4[m->m_numVertices];
    m->m_colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    m->m_colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
    m->m_colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

    m->bufferData();
    m->generateNormals();

    return m;
  }

  /**
   * @brief Generates a line between two points.
   * @param from Start point
   * @param to End point
   * @return Mesh containing line
   */
  Mesh *Mesh::GenerateLine(const Vector3 &from, const Vector3 &to)
  {
    Mesh *m = new Mesh();
    m->m_type = GL_LINES;
    m->m_numVertices = 2;

    m->m_vertices = new Vector3[m->m_numVertices];
    m->m_vertices[0] = from;
    m->m_vertices[1] = to;

    m->m_textureCoords = new Vector2[m->m_numVertices];
    m->m_textureCoords[0] = Vector2(1.0f, 1.0f);
    m->m_textureCoords[1] = Vector2(0.0f, 1.0f);

    m->m_colours = new Vector4[m->m_numVertices];
    m->m_colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    m->m_colours[1] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

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
  Mesh *Mesh::GenerateRing2D(float radiusOuter, float radiusInner,
                             int resolution)
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

      m->m_vertices[n] =
          Vector3(cos(a) * radiusOuter, sin(a) * radiusOuter, 0.0f);
      m->m_colours[n] = c;
      m->m_textureCoords[n] = Vector2(abs(cos(a)), abs(sin(a)));
      n++;

      m->m_vertices[n] =
          Vector3(cos(a) * radiusInner, sin(a) * radiusInner, 0.0f);
      m->m_colours[n] = c;
      m->m_textureCoords[n] = Vector2(abs(cos(a)), abs(sin(a)));
      n++;
    }

    // m->generateNormals();
    m->bufferData();
    return m;
  }

  /**
   * @brief Loads a mesh from an ASCII file.
   * @param filename Filename to load
   * @return Mesh containing loaded mesh
   */
  Mesh *Mesh::LoadASCIIMeshFile(const string &filename)
  {
    ifstream f(filename);

    if (!f)
      return NULL;

    Mesh *m = new Mesh();
    m->m_type = GL_TRIANGLES;
    f >> m->m_numVertices;

    int hasTex = 0;
    int hasColour = 0;

    f >> hasTex;
    f >> hasColour;

    m->m_vertices = new Vector3[m->m_numVertices];

    if (hasTex)
    {
      m->m_textureCoords = new Vector2[m->m_numVertices];
      m->m_colours = new Vector4[m->m_numVertices];
    }

    for (unsigned int i = 0; i < m->m_numVertices; ++i)
    {
      f >> m->m_vertices[i][0];
      f >> m->m_vertices[i][1];
      f >> m->m_vertices[i][2];
    }

    if (hasColour)
    {
      for (unsigned int i = 0; i < m->m_numVertices; ++i)
      {
        unsigned int r, g, b, a;

        f >> r;
        f >> g;
        f >> b;
        f >> a;
        m->m_colours[i] =
            Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
      }
    }

    if (hasTex)
    {
      for (unsigned int i = 0; i < m->m_numVertices; ++i)
      {
        f >> m->m_textureCoords[i][0];
        f >> m->m_textureCoords[i][1];
      }
    }

    m->generateNormals();
    m->bufferData();
    return m;
  }

  /**
   * @brief Loads a mesh from a model file (supported by Assimp).
   * @param filename Filename to load
   * @param meshIdx Index of mesh (within scene) to load
   * @return Mesh containing loaded model
   */
  Mesh *Mesh::LoadModelFile(const string &filename, size_t meshIdx)
  {
    Assimp::Importer i;
    const struct aiScene *scene =
        i.ReadFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

    if (meshIdx > scene->mNumMeshes)
      return NULL;

    Mesh *m = new Mesh();
    m->m_type = GL_TRIANGLES;
    // m->m_type = GL_LINES;

    aiMesh *mesh = scene->mMeshes[meshIdx];
    aiVector3D *vertices = mesh->mVertices;

    m->m_numVertices = mesh->mNumVertices * 3;
    m->m_vertices = new Vector3[m->m_numVertices];
    m->m_colours = new Vector4[m->m_numVertices];

    // Load vertices
    size_t idx = 0;
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
      const aiFace &face = mesh->mFaces[i];

      const aiVector3D &v0 = vertices[face.mIndices[0]];
      const aiVector3D &v1 = vertices[face.mIndices[1]];
      const aiVector3D &v2 = vertices[face.mIndices[2]];

      m->m_colours[idx] = Vector4(1, 1, 1, 1);
      m->m_vertices[idx++] = Vector3(v0[0], v0[1], v0[2]);

      m->m_colours[idx] = Vector4(1, 1, 1, 1);
      m->m_vertices[idx++] = Vector3(v1[0], v1[1], v1[2]);

      m->m_colours[idx] = Vector4(1, 1, 1, 1);
      m->m_vertices[idx++] = Vector3(v2[0], v2[1], v2[2]);
    }

    // Normalise vertex coordinates to 1
    std::pair<Vector3, Vector3> bBox = GetBoundingBox(m);
    Vector3 norm = bBox.second;
    if (bBox.first.length2() > bBox.second.length2())
      norm = bBox.first;

    for (size_t i = 0; i < m->m_numVertices; i++)
      m->m_vertices[i] = m->m_vertices[i] / norm;

    m->generateNormals();
    m->bufferData();

    return m;
  }
}
}
