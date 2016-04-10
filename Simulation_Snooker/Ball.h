/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATION_SNOOKER_BALL_H_
#define _SIMULATION_SNOOKER_BALL_H_

#include <Engine_Graphics/Colour.h>
#include <Engine_Graphics/RenderableObject.h>

#include <Simulation_Physics/SphericalEntity.h>

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

  public:
    Ball(const Engine::Maths::Vector2 &pos, int points);
    virtual ~Ball();

    /**
     * @brief Gets the number of points this ball is worth.
     * @return Point value.
     */
    inline int points() const
    {
      return m_points;
    }

    void reset(bool positionOnly = false);

    Engine::Graphics::Colour colour(float alpha = 1.0f) const;
    bool isCueBall() const;

    virtual void setPosition(const Engine::Maths::Vector2 &pos);

  private:
    int m_points;                             //!< Number of points potting this ball gets
    Engine::Maths::Vector2 m_defaultPosition; //!< Default position of this ball on the table
  };
}
}

#endif
