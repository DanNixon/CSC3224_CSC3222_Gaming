/**
 * @file
 * @author Dan Nixon
 */

#include "Table.h"

#include <Mesh.h>
#include <Texture.h>
#include <Shaders.h>

using namespace Engine::Maths;
using namespace Engine::Graphics;

/**
 * @brief Dimensions of the table in mm.
 */
const Vector2 Table::DIMENSIONS = Vector2(3569.0f, 1778.0f);

/**
 * @brief Half the dimensions of the table in mm.
 */
const Vector2 Table::HALF_DIMENSIONS = DIMENSIONS / 2;

/**
 * @brief Creates a new table.
 */
Table::Table()
    : RenderableObject(Mesh::GenerateRect2D(DIMENSIONS), NULL)
{
  ShaderProgram *sp = new ShaderProgram();
  sp->addShader(new VertexShader("vert.glsl"));
  sp->addShader(new FragmentShader("frag_tex.glsl"));
  sp->link();
  setShader(sp);

  Texture *tex = new Texture("tabletopTex");
  tex->load("table.bmp");
  setTexture(tex);

  m_cushions[0] = new Cushion(Vector2(-HALF_DIMENSIONS.x(), 0.0f), 1);
  m_cushions[1] = new Cushion(Vector2(HALF_DIMENSIONS.x(), 0.0f), -1);
  m_cushions[2] = new Cushion(Vector2(0.0f, -HALF_DIMENSIONS.y()), 1);
  m_cushions[3] = new Cushion(Vector2(0.0f, HALF_DIMENSIONS.y()), -1);
}

Table::~Table()
{
  for (size_t i = 0; i < 4; i++)
    delete m_cushions[i];
}
