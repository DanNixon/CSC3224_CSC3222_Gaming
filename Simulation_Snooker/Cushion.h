/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATION_SNOOKER_CUSHION_H_
#define _SIMULATION_SNOOKER_CUSHION_H_

#include <PlanarEntity.h>

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