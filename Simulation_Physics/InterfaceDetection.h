/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_PHYSICS_INTERFACEDETECTION_H_
#define _SIMULATION_PHYSICS_INTERFACEDETECTION_H_

#include "Entity.h"
#include "InterfaceDef.h"

namespace Simulation
{
namespace Physics
{
  class SphericalEntity;
  class PlanarEntity;

  /**
   * @class InterfaceDetection
   * @brief Contains tests for interface between two entities.
   * @author Dan Nixon
   */
  class InterfaceDetection
  {
  public:
    static bool Detect(InterfaceDef &interf);

    static void SphereSphere(bool &result, Engine::Maths::Vector2 &normal, const SphericalEntity *a,
                             const SphericalEntity *b);
    static void SpherePlane(bool &result, Engine::Maths::Vector2 &normal, const SphericalEntity *a,
                            const PlanarEntity *b);
  };
}
}

#endif