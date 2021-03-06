/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#ifndef _SIMULATION_SNOOKER_CUSHION_H_
#define _SIMULATION_SNOOKER_CUSHION_H_

#include <Simulation_Physics/PlanarEntity.h>

namespace Simulation
{
namespace Snooker
{
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
}
}

#endif