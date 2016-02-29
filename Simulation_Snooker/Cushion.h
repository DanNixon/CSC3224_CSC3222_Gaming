/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATIONSNOOKER_CUSHION_H_
#define _SIMULATIONSNOOKER_CUSHION_H_

#include <PlanarEntity.h>

/**
 * @class Cushion
 * @brief Represents a side cushion of the snooker table.
 * @author Dan Nixon
 */
class Cushion : public Simulation::Physics::PlanarEntity
{
public:
  Cushion(const Engine::Maths::Vector2 &pos);
  virtual ~Cushion();
};

#endif