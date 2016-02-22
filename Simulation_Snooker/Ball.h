/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <SphericalEntity.h>

/**
 * @class Ball
 * @brief Represents a snooker ball.
 * @author Dan Nixon
 */
class Ball : public Simulation::Physics::SphericalEntity
{
public:
  Ball(const Engine::Maths::Vector2 &pos);
  virtual ~Ball();
};
