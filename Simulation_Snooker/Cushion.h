/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <PlanarEntity.h>

/**
 * @class Cushion
 * @brief Represents a side cushion of the snooker table.
 * @author Dan Nixon
 */
class Cushion : public Simulation::Physics::PlanarEntity
{
public:
  Cushion(const Engine::Maths::Vector2 &pos, int direction);
  virtual ~Cushion();
};
