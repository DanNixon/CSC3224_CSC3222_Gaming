/**
* @file
* @author Dan Nixon
*/

#include "Ball.h"

#include <Mesh.h>
#include <Shaders.h>

using namespace Engine::Maths;
using namespace Engine::Graphics;

/**
 * @copydoc SphericalEntity::SphericalEntity(const Vector2 &)
 */
Ball::Ball(const Vector2 &pos, int points)
    : SphericalEntity(pos, RADIUS)
    , RenderableObject(Mesh::GenerateDisc2D(RADIUS), NULL)
    , m_points(points)
{
  ShaderProgram * sp = new ShaderProgram();
  sp->addShader(new VertexShader("vert.glsl"));
  sp->addShader(new FragmentShader("frag_col.glsl"));
  sp->link();
  setShader(sp);

  // Set correct ball colour
  mesh()->setStaticColour(colour());

  // Set initial position
  setPosition(pos);
}

Ball::~Ball()
{
}

Vector4 Ball::colour(float alpha) const
{
  switch (m_points)
  {
  case -1:
    return Vector4(1.0f, 1.0f, 1.0f, alpha); // White (cue ball)
  case 1:
    return Vector4(1.0f, 1.0f, 1.0f, alpha); // Red
  case 2:
    return Vector4(1.0f, 1.0f, 0.0f, alpha); // Yellow
  case 3:
    return Vector4(0.0f, 1.0f, 0.0f, alpha); // Green
  case 4:
    return Vector4(0.8f, 0.2f, 0.2f, alpha); // Brown
  case 5:
    return Vector4(0.0f, 0.0f, 1.0f, alpha); // Blue
  case 6:
    return Vector4(1.0f, 0.75f, 0.8f, alpha); // Pink
  case 7:
    return Vector4(0.0f, 0.0f, 0.0f, alpha); // Black
  default:
    return Vector4(1.0f, 0.0f, 1.0f, 1.0f); // Magenta (invalid points)
  }
}

void Ball::setPosition(const Engine::Maths::Vector2 &pos)
{
  SphericalEntity::setPosition(pos);
  setModelMatrix(Matrix4::Translation(Vector3(pos.x(), pos.y(), 1.0f)));
}