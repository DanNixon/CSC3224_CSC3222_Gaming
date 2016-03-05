/**
* @file
* @author Dan Nixon
*/

#include "Pocket.h"

#include <Mesh.h>
#include <Shaders.h>

#include "Ball.h"

using namespace Engine::Maths;
using namespace Engine::Graphics;

/**
 * @brief Radius of a Pocket in mm.
 */
const float Pocket::RADIUS = 44.45f;

/**
 * @copydoc SphericalEntity::SphericalEntity(const Vector2 &)
 * @param pos Position of the pocket
 */
Pocket::Pocket(const Vector2 &pos)
    : SphericalEntity(pos, std::numeric_limits<float>::max(), RADIUS, true, 0.99f, 0.005f, Ball::RADIUS)
    , RenderableObject(Mesh::GenerateDisc2D(RADIUS), NULL)
{
  ShaderProgram *sp = new ShaderProgram();
  sp->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
  sp->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
  sp->link();
  setShader(sp);

  // Set initial position
  setPosition(pos);
}

Pocket::~Pocket()
{
}

//TEMP
void Pocket::setPosition(const Engine::Maths::Vector2 &pos)
{
  SphericalEntity::setPosition(pos);
  setModelMatrix(Matrix4::Translation(Vector3(pos.x(), pos.y(), 0.0f)));
}
