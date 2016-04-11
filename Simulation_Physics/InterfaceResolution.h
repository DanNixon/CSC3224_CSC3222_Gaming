/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#ifndef _SIMULATION_PHYSICS_INTERFACERESOLUTION_H_
#define _SIMULATION_PHYSICS_INTERFACERESOLUTION_H_

#include "Entity.h"
#include "InterfaceDef.h"

namespace Simulation
{
namespace Physics
{
  /**
   * @class InterfaceResolution
   * @brief Contains functions for resolving interfaces between objects.
   * @author Dan Nixon
   */
  class InterfaceResolution
  {
  public:
    static void Impulse(InterfaceDef &interf, float epsilon);
  };
}
}

#endif
