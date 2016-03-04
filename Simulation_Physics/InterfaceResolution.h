/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_PHYSICS_INTERFACERESOLUTION_H_
#define _SIMULATION_PHYSICS_INTERFACERESOLUTION_H_

#include "Entity.h"

namespace Simulation
{
  namespace Physics
  {
    class InterfaceResolution
    {
    public:
      static Engine::Maths::Vector2 InterfaceNormal(Entity &a, Entity &b);

      static void Impulse(Entity &a, Entity &b, float epsilon);
    };
  }
}

#endif