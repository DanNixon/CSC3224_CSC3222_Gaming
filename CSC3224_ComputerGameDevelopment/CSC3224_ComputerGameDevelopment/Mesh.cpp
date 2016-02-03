#include "Mesh.h"

Mesh::Mesh()
  : numIndices(0),
  type(GL_TRIANGLES),
  vertices(NULL),
  textureCoords(NULL),
  normals(NULL),
  tangents(NULL),
  indices(NULL),
  colours(NULL)
{
  glGenVertexArrays(1, &arrayObject);

  for (int i = 0; i < MAX_BUFFER; ++i)
    bufferObject[i] = 0;
}

Mesh::~Mesh(void)
{
  glDeleteVertexArrays(1, &arrayObject);
  glDeleteBuffers(MAX_BUFFER, bufferObject);

  delete[] vertices;
  delete[] indices;
  delete[] textureCoords;
  delete[] tangents;
  delete[] normals;
  delete[] colours;
}

void Mesh::Draw()
{
  glBindVertexArray(arrayObject);

  if (bufferObject[INDEX_BUFFER])
    glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(type, 0, numVertices);

  glBindVertexArray(0);
}

/**
 * @brief Buffers all VBO data into graphics memory.
 *
 * Required before drawing!
 */
void Mesh::BufferData()
{
  glBindVertexArray(arrayObject);

  glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
  glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), vertices,
    GL_STATIC_DRAW);
  glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(VERTEX_BUFFER);

  //Buffer texture data
  if (textureCoords)
  {
    glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector2), textureCoords,
      GL_STATIC_DRAW);
    glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(TEXTURE_BUFFER);
  }

  // buffer colour data
  if (colours)
  {
    glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector4), colours,
      GL_STATIC_DRAW);
    glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(COLOUR_BUFFER);
  }

  // buffer index data
  if (indices)
  {
    glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices,
      GL_STATIC_DRAW);
  }

  if (normals)
  {
    glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), normals,
      GL_STATIC_DRAW);

    glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(NORMAL_BUFFER);
  }

  glBindVertexArray(0);
}

void Mesh::GenerateNormals()
{
  if (!normals)
    normals = new Vector3[numVertices];

  for (unsigned int i = 0; i < numVertices; i += 3)
  {
    Vector3 &a = vertices[i];
    Vector3 &b = vertices[i + 1];
    Vector3 &c = vertices[i + 2];

    Vector3 normal = Vector3::Cross(b - a, c - a);
    normal.Normalise();

    normals[i] = normal;
    normals[i + 1] = normal;
    normals[i + 2] = normal;
  }
}


Mesh *Mesh::GenerateTriangle()
{
  Mesh *m = new Mesh();
  m->numVertices = 3;

  m->vertices = new Vector3[m->numVertices];
  m->vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
  m->vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
  m->vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);

  m->textureCoords = new Vector2[m->numVertices];
  m->textureCoords[0] = Vector2(0.5f, 0.0f);
  m->textureCoords[1] = Vector2(1.0f, 1.0f);
  m->textureCoords[2] = Vector2(0.0f, 1.0f);

  m->colours = new Vector4[m->numVertices];
  m->colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
  m->colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
  m->colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

  m->BufferData();
  m->GenerateNormals();

  return m;
}

Mesh *Mesh::GenerateLine(const Vector3 &from, const Vector3 &to)
{
  Mesh *m = new Mesh();
  m->type = GL_LINES;
  m->numVertices = 2;

  m->vertices = new Vector3[m->numVertices];
  m->vertices[0] = from;
  m->vertices[1] = to;

  m->textureCoords = new Vector2[m->numVertices];
  m->textureCoords[0] = Vector2(1.0f, 1.0f);
  m->textureCoords[1] = Vector2(0.0f, 1.0f);

  m->colours = new Vector4[m->numVertices];
  m->colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
  m->colours[1] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

  m->BufferData();

  return m;
}

Mesh *Mesh::LoadMeshFile(const string &filename)
{
  ifstream f(filename);

  if (!f)
  {
    return NULL;
  }

  Mesh *m = new Mesh();
  m->type = GL_TRIANGLES;
  f >> m->numVertices;

  int hasTex = 0;
  int hasColour = 0;

  f >> hasTex;
  f >> hasColour;

  m->vertices = new Vector3[m->numVertices];

  if (hasTex)
  {
    m->textureCoords = new Vector2[m->numVertices];
    m->colours = new Vector4[m->numVertices];
  }

  for (unsigned int i = 0; i < m->numVertices; ++i)
  {
    f >> m->vertices[i].x;
    f >> m->vertices[i].y;
    f >> m->vertices[i].z;
  }

  if (hasColour)
  {
    for (unsigned int i = 0; i < m->numVertices; ++i)
    {
      unsigned int r, g, b, a;

      f >> r;
      f >> g;
      f >> b;
      f >> a;
      // OpenGL can use floats for colours directly - this will take up 4x as
      // much space, but could avoid any byte / float conversions happening
      // behind the scenes in our shader executions
      m->colours[i] = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }
  }

  if (hasTex)
  {
    for (unsigned int i = 0; i < m->numVertices; ++i)
    {
      f >> m->textureCoords[i].x;
      f >> m->textureCoords[i].y;
    }
  }

  m->GenerateNormals();
  m->BufferData();
  return m;
}