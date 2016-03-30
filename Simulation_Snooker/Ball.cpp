/**
* @file
* @author Dan Nixon
*/

#include "Ball.h"

#include <Engine_Graphics/Mesh.h>
#include <Engine_Graphics/Shaders.h>

using namespace Engine::Maths;
using namespace Engine::Graphics;

namespace Simulation
{
namespace Snooker
{

  /**
   * @brief Radius of a ball in mm.
   */
  const float Ball::RADIUS = 26.25f;

  /**
  * @brief Mass of a ball in g.
  */
  const float Ball::MASS = 100.0f;

  /**
   * @brief Gets info about a snooker ball.
   * @param points Number of points the ball is worth (-1 for cue ball)
   * @return Pair of name and colour
   */
  std::pair<std::string, Colour> Ball::Info(int points)
  {
    switch (points)
    {
    case -1:
      return std::make_pair("cue_ball", Colour(1.0f, 1.0f, 1.0f));
    case 1:
      return std::make_pair("red", Colour(1.0f, 0.0f, 0.0f));
    case 2:
      return std::make_pair("yellow", Colour(1.0f, 1.0f, 0.0f));
    case 3:
      return std::make_pair("green", Colour(0.0f, 1.0f, 0.0f));
    case 4:
      return std::make_pair("brown", Colour(0.8f, 0.2f, 0.2f));
    case 5:
      return std::make_pair("blue", Colour(0.0f, 0.0f, 1.0f));
    case 6:
      return std::make_pair("pink", Colour(1.0f, 0.75f, 0.8f));
    case 7:
      return std::make_pair("black", Colour(0.0f, 0.0f, 0.0f));
    default:
      return std::make_pair("", Colour(1.0f, 0.0f, 1.0f));
    }
  }

  /**
   * @copydoc SphericalEntity::SphericalEntity(const Vector2 &)
   * @param pos Position of the ball
   * @param points Number of points awarded for potting this ball (-1 for cue
   *               ball)
   */
  Ball::Ball(const Vector2 &pos, int points)
      : SphericalEntity(pos, MASS, RADIUS, false, 0.99f, 0.005f)
      , RenderableObject(Info(points).first, Mesh::GenerateDisc2D(RADIUS), nullptr)
      , m_points(points)
  {
    ShaderProgram *sp = new ShaderProgram();
    sp->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    sp->addShader(new FragmentShader("../resources/shader/frag_col.glsl"));
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

  /**
   * @brief Gets the colour of this ball.
   * @param alpha Alpha channel intensity (defaults to 1.0)
   * @return Ball colour
   *
   * Colour is determined by the number of points (-1 being the cue ball).
   */
  Colour Ball::colour(float alpha) const
  {
    Colour c = Info(m_points).second;
    c[3] = alpha;
    return c;
  }

  /**
   * @brief Test to see if this is the cue ball (based on points).
   * @return True if this is the cue ball.
   */
  bool Ball::isCueBall() const
  {
    return m_points == -1;
  }

  /**
   * @copydoc SphericalEntity::setPosition
   */
  void Ball::setPosition(const Engine::Maths::Vector2 &pos)
  {
    SphericalEntity::setPosition(pos);
    setModelMatrix(Matrix4::Translation(Vector3(pos.x(), pos.y(), 0.0f)));
  }
}
}