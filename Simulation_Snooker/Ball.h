/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATION_SNOOKER_BALL_H_
#define _SIMULATION_SNOOKER_BALL_H_

#include <Colour.h>
#include <RenderableObject.h>
#include <SphericalEntity.h>

namespace Simulation
{
namespace Snooker
{
  /**
   * @class Ball
   * @brief Represents a snooker ball.
   * @author Dan Nixon
   */
  class Ball : public Simulation::Physics::SphericalEntity, public Engine::Graphics::RenderableObject
  {
  public:
    static const float RADIUS;
    static const float MASS;

    static std::pair<std::string, Engine::Graphics::Colour> Ball::Info(int points);

    Ball(const Engine::Maths::Vector2 &pos, int points);
    virtual ~Ball();

    Engine::Graphics::Colour colour(float alpha = 1.0f) const;
    bool isCueBall() const;

    virtual void setPosition(const Engine::Maths::Vector2 &pos);

  private:
    int m_points; //!< Number of points potting this ball gets
  };
}
}

#endif