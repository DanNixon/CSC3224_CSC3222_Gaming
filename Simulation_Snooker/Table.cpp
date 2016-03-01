/**
 * @file
 * @author Dan Nixon
 */

#include "Table.h"

#include <Mesh.h>
#include <Shaders.h>
#include <Texture.h>

using namespace Engine::Maths;
using namespace Engine::Graphics;

/**
 * @brief Dimensions of the table in mm.
 */
const Vector2 Table::DIMENSIONS = Vector2(3880.0f, 2080.0f);

/**
 * @brief Half the dimensions of the table in mm.
 */
const Vector2 Table::HALF_DIMENSIONS = DIMENSIONS / 2;

/**
 * @brief Dimensions of the play area in mm.
 */
const Vector2 Table::PLAY_AREA = Vector2(3568.7f, 1778.0f);

/**
 * @brief Half the dimensions of the play area in mm.
 */
const Vector2 Table::HALF_PLAY_AREA = PLAY_AREA / 2;

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

  m_cushions[0] = new Cushion(Vector2(-HALF_PLAY_AREA.x(), 0.0f));
  m_cushions[1] = new Cushion(Vector2(HALF_PLAY_AREA.x(), 0.0f));
  m_cushions[2] = new Cushion(Vector2(0.0f, -HALF_PLAY_AREA.y()));
  m_cushions[3] = new Cushion(Vector2(0.0f, HALF_PLAY_AREA.y()));
}

Table::~Table()
{
  for (size_t i = 0; i < 4; i++)
    delete m_cushions[i];
}
