/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_PHYSICS_INTERFACEDETECTION_H_
#define _SIMULATION_PHYSICS_INTERFACEDETECTION_H_

#include "Entity.h"

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
    static bool Detect(const Entity &a, const Entity &b);

    static void SphereSphere(bool &result, const SphericalEntity &a,
                             const SphericalEntity &b);
    static void PlanePlane(bool &result, const PlanarEntity &a,
                           const PlanarEntity &b);
    static void SpherePlane(bool &result, const SphericalEntity &a,
                            const PlanarEntity &b);
  };
}
}

#endif