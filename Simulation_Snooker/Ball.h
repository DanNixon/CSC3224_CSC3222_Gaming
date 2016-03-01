/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATIONSNOOKER_BALL_H_
#define _SIMULATIONSNOOKER_BALL_H_

#include <RenderableObject.h>
#include <SphericalEntity.h>
#include <Vector4.h>

/**
 * @class Ball
 * @brief Represents a snooker ball.
 * @author Dan Nixon
 */
class Ball : public Simulation::Physics::SphericalEntity,
             public Engine::Graphics::RenderableObject
{
public:
  static const float RADIUS;

  Ball(const Engine::Maths::Vector2 &pos, int points);
  virtual ~Ball();

  Engine::Maths::Vector4 colour(float alpha = 1.0f) const;

  virtual void setPosition(const Engine::Maths::Vector2 &pos);

private:
  int m_points; //!< Number of points potting this ball gets
};

#endif