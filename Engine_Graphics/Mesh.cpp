/**
 * @file
 * @author Dan Nixon
 */

#include "Mesh.h"

#include <Engine_Maths/VectorOperations.h>
#include <Engine_Maths/math_common.h>

using namespace Engine::Maths;

namespace Engine
{
namespace Graphics
{
  /**
   * @brief Creates a new empty mesh.
   */
  Mesh::Mesh()
      : m_numIndices(0)
      , m_type(GL_TRIANGLES)
      , m_vertices(nullptr)
      , m_colours(nullptr)
      , m_textureCoords(nullptr)
      , m_normals(nullptr)
      , m_tangents(nullptr)
      , m_indices(nullptr)
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
   * @brief Draws the mesh.
   * @param program The shader program used to draw the mesh
   */
  void Mesh::draw(GLuint program)
  {
    glUniform4fv(glGetUniformLocation(program, "ambientColour"), 1, (float *)&m_ambientColour);
    glUniform4fv(glGetUniformLocation(program, "diffuseColour"), 1, (float *)&m_diffuseColour);
    glUniform4fv(glGetUniformLocation(program, "specularColour"), 1, (float *)&m_specularColour);
    glUniform1f(glGetUniformLocation(program, "ambientStrength"), 0.2f);
    glUniform1f(glGetUniformLocation(program, "shininess"), m_shininess);
    glUniform1f(glGetUniformLocation(program, "shininessStrength"), m_shininessStrength);

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
  void Mesh::setStaticColour(const Colour &col)
  {
    if (m_colours != nullptr)
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
    m->m_colours = new Colour[m->m_numVertices];
    m->m_textureCoords = new Vector2[m->m_numVertices];

    const float deltaA = ((PI * 2) / resolution);

    // "Origin" vertex
    m->m_vertices[0] = Vector3(0.0f, 0.0f, 0.0f);
    m->m_boundingBox.resizeByPoint(m->m_vertices[0]);
    m->m_colours[0] = Colour(1.0f, 1.0f, 1.0f, 1.0f);
    m->m_textureCoords[0] = Vector2(0.5f, 0.5f);

    for (int i = 1; i < resolution + 2; ++i)
    {
      const float a = i * deltaA;

      m->m_vertices[i] = Vector3(cos(a) * radius, sin(a) * radius, 0.0f);
      m->m_boundingBox.resizeByPoint(m->m_vertices[i]);
      m->m_colours[i] = Colour(1.0f, 1.0f, 1.0f, 1.0f);
      m->m_textureCoords[i] = Vector2(abs(cos(a)), abs(sin(a)));
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
    m->m_colours = new Colour[m->m_numVertices];
    m->m_textureCoords = new Vector2[m->m_numVertices];

    const float deltaA = ((PI * 2) / resolution);
    const Colour c(1, 1, 1, 127);

    int n = 0;
    for (int i = 0; i < resolution + 2; i++)
    {
      const float a = i * deltaA;

      m->m_vertices[n] = Vector3(cos(a) * radiusOuter, sin(a) * radiusOuter, 0.0f);
      m->m_boundingBox.resizeByPoint(m->m_vertices[n]);
      m->m_colours[n] = c;
      m->m_textureCoords[n] = Vector2(abs(cos(a)), abs(sin(a)));
      n++;

      m->m_vertices[n] = Vector3(cos(a) * radiusInner, sin(a) * radiusInner, 0.0f);
      m->m_boundingBox.resizeByPoint(m->m_vertices[n]);
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
  Mesh *Mesh::LoadMesh(const struct aiMesh *mesh, const struct aiMaterial *material)
  {
    Mesh *m = new Mesh();

    // Check if this should be rendered as a wireframe
    int wireFrame = 0;
    bool lines = AI_SUCCESS == aiGetMaterialInteger(material, AI_MATKEY_ENABLE_WIREFRAME, &wireFrame) && wireFrame;
    m->m_type = lines ? GL_LINES : GL_TRIANGLES;

    aiVector3D *vertices = mesh->mVertices;

    const bool hasColours = mesh->mColors[0] != nullptr;
    const bool hasTexCoords = mesh->HasTextureCoords(0);
    const bool hasNormals = mesh->HasNormals();

    // Allocate storage
    m->m_numVertices = mesh->mNumFaces * 3;
    m->m_vertices = new Vector3[m->m_numVertices];
    m->m_colours = new Colour[m->m_numVertices];
    if (hasTexCoords)
      m->m_textureCoords = new Vector2[m->m_numVertices];
    if (hasNormals)
      m->m_normals = new Vector3[m->m_numVertices];

    // Get lighting data
    aiColor4D c;

    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &c))
      m->m_ambientColour = Colour(c);

    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &c))
      m->m_diffuseColour = Colour(c);

    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &c))
      m->m_specularColour = Colour(c);

    aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &(m->m_shininess));
    aiGetMaterialFloat(material, AI_MATKEY_SHININESS_STRENGTH, &(m->m_shininessStrength));

    // Load vertices
    size_t idx = 0;
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
      const aiFace &face = mesh->mFaces[i];

      for (size_t j = 0; j < 3; j++)
      {
        int index = face.mIndices[j];

        const aiVector3D &v = vertices[index];

        if (hasColours)
          m->m_colours[idx] = Colour(mesh->mColors[0][index]);
        else
          m->m_colours[idx] = Colour(1.0f, 1.0f, 1.0f, 1.0f);

        if (hasTexCoords)
        {
          const aiVector3D &tex = mesh->mTextureCoords[0][index];
          m->m_textureCoords[idx] = Vector2(tex[0], tex[1]);
        }

        if (hasNormals)
        {
          const aiVector3D &norm = mesh->mNormals[index];
          m->m_normals[idx] = Vector3(norm.x, norm.y, norm.z);
        }

        Vector3 vtx(v[0], v[1], v[2]);
        m->m_boundingBox.resizeByPoint(vtx);
        m->m_vertices[idx++] = vtx;
      }
    }

    // Calculate normals if the model does not have any
    if (!hasNormals)
      m->generateNormals();

    m->bufferData();

    return m;
  }
}
}
