#include "Mesh.h"

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

void Mesh::draw()
{
  glBindVertexArray(m_arrayObject);

  if (m_bufferObject[INDEX_BUFFER])
    glDrawElements(m_type, m_numIndices, GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(m_type, 0, m_numVertices);

  glBindVertexArray(0);
}

void Mesh::generateNormals()
{
  if (!m_normals)
    m_normals = new Vector3[m_numVertices];

  for (unsigned int i = 0; i < m_numVertices; i += 3)
  {
    Vector3 &a = m_vertices[i];
    Vector3 &b = m_vertices[i + 1];
    Vector3 &c = m_vertices[i + 2];

    Vector3 normal = Vector3::Cross(b - a, c - a);
    normal.Normalise();

    m_normals[i] = normal;
    m_normals[i + 1] = normal;
    m_normals[i + 2] = normal;
  }
}

/**
 * @brief Buffers all VBO data into graphics memory.
 *
 * Required before drawing!
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

  // Buffer texture data
  if (m_textureCoords)
  {
    glGenBuffers(1, &m_bufferObject[TEXTURE_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[TEXTURE_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector2),
                 m_textureCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(TEXTURE_BUFFER);
  }

  // buffer colour data
  if (m_colours)
  {
    glGenBuffers(1, &m_bufferObject[COLOUR_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[COLOUR_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector4), m_colours,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(COLOUR_BUFFER);
  }

  // buffer index data
  if (m_indices)
  {
    glGenBuffers(1, &m_bufferObject[INDEX_BUFFER]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferObject[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLuint),
                 m_indices, GL_STATIC_DRAW);
  }

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

Mesh *Mesh::LoadMeshFile(const string &filename)
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
    f >> m->m_vertices[i].x;
    f >> m->m_vertices[i].y;
    f >> m->m_vertices[i].z;
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
      m->m_colours[i] = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }
  }

  if (hasTex)
  {
    for (unsigned int i = 0; i < m->m_numVertices; ++i)
    {
      f >> m->m_textureCoords[i].x;
      f >> m->m_textureCoords[i].y;
    }
  }

  m->generateNormals();
  m->bufferData();
  return m;
}
