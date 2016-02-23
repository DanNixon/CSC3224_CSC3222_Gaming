/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <RenderableObject.h>
#include <Vector4.h>
#include <SphericalEntity.h>

/**
 * @class Ball
 * @brief Represents a snooker ball.
 * @author Dan Nixon
 */
class Ball : public Simulation::Physics::SphericalEntity,
             public Engine::Graphics::RenderableObject
{
public:
  /**
   * @brief Radius of a ball in mm.
   */
  static const int RADIUS = 21;

  Ball(const Engine::Maths::Vector2 &pos, int points);
  virtual ~Ball();

  Engine::Maths::Vector4 colour(float alpha = 1.0f) const;

  virtual void setPosition(const Engine::Maths::Vector2 &pos);

private:
  int m_points; //!< Number of points potting this ball gets
};
