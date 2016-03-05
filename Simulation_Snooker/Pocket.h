/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATIONSNOOKER_POCKET_H_
#define _SIMULATIONSNOOKER_POCKET_H_

#include <RenderableObject.h>
#include <SphericalEntity.h>
#include <Vector4.h>

/**
 * @class Pocket
 * @brief Represents a snooker pocket.
 * @author Dan Nixon
 */
class Pocket : public Simulation::Physics::SphericalEntity,
               public Engine::Graphics::RenderableObject
{
public:
  static const float RADIUS;

  Pocket(const Engine::Maths::Vector2 &pos);
  virtual ~Pocket();

  // TEMP
  virtual void setPosition(const Engine::Maths::Vector2 &pos);
};

#endif