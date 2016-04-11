/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#include "Pocket.h"

#include <Engine_Graphics/Mesh.h>
#include <Engine_Graphics/Shaders.h>

#include "Ball.h"

using namespace Engine::Maths;
using namespace Engine::Graphics;

namespace Simulation
{
namespace Snooker
{
  /**
   * @brief Radius of a Pocket in mm.
   *
   * Radius is the correct pocket size minus half ball radius to give the
   * correct collision sphere size such that at the point of interface between
   * a ball and pocket the centre of the ball is just over the graphical edge
   * of the procet.
   */
  const float Pocket::RADIUS = 44.45f - (Ball::RADIUS / 2.0f);

  /**
   * @copydoc SphericalEntity::SphericalEntity(const Vector2 &)
   * @param pos Position of the pocket
   */
  Pocket::Pocket(const Vector2 &pos)
      : SphericalEntity(pos, std::numeric_limits<float>::max(), RADIUS, true, 0.99f, 0.005f, Ball::RADIUS)
      , RenderableObject("pocket", Mesh::GenerateDisc2D(RADIUS), nullptr)
  {
    ShaderProgram *sp = new ShaderProgram();
    sp->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    sp->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
    sp->link();
    setShader(sp);

    // Set initial position
    setPosition(pos);

    // Invisible by default
    setActive(false);
  }

  Pocket::~Pocket()
  {
  }

  /**
   * @copydoc SphericalEntity::setPosition
   */
  void Pocket::setPosition(const Engine::Maths::Vector2 &pos)
  {
    SphericalEntity::setPosition(pos);

    // Graphical mesh position
    setModelMatrix(Matrix4::Translation(Vector3(pos.x(), pos.y(), 0.0f)));

    // Bounding box position
    m_box = m_originBox;
    m_box += pos;
  }
}
}
