/**
 * @file
 * @author Dan Nixon
 */

#include "InterfaceDetection.h"

#include <Vector2.h>
#include <VectorOperations.h>

#include "PlanarEntity.h"
#include "SphericalEntity.h"

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @brief Tests for interface between two entities.
   * @param a First entity
   * @param b Second entity
   * @return True if entities interface
   *
   * Will also return false if no interface test between the two entities is
   *known.
   */
  bool InterfaceDetection::Detect(const Entity &a, const Entity &b)
  {
    bool retVal = false;

    if (dynamic_cast<const SphericalEntity *>(&a) &&
        dynamic_cast<const SphericalEntity *>(&b))
      SphereSphere(retVal, static_cast<const SphericalEntity &>(a),
                   static_cast<const SphericalEntity &>(b));

    else if (dynamic_cast<const PlanarEntity *>(&a) &&
             dynamic_cast<const PlanarEntity *>(&b))
      PlanePlane(retVal, static_cast<const PlanarEntity &>(a),
                 static_cast<const PlanarEntity &>(b));

    else if (dynamic_cast<const SphericalEntity *>(&a) &&
             dynamic_cast<const PlanarEntity *>(&b))
      SpherePlane(retVal, static_cast<const SphericalEntity &>(a),
                  static_cast<const PlanarEntity &>(b));

    else if (dynamic_cast<const PlanarEntity *>(&a) &&
             dynamic_cast<const SphericalEntity *>(&b))
      SpherePlane(retVal, static_cast<const SphericalEntity &>(b),
                  static_cast<const PlanarEntity &>(a));

    return retVal;
  }

  /**
   * @brief Tests for interface between two spherical entities.
   * @param result [out] Result of test
   * @param a First spherical entity
   * @param b Second spherical entity
   */
  void InterfaceDetection::SphereSphere(bool &result, const SphericalEntity &a,
                                        const SphericalEntity &b)
  {
    float d = VectorOperations::Distance2(a.position(), b.position());
    float r = a.radius() + b.radius();
    r *= r;
    result = (d < r);
  }

  /**
   * @brief Tests for interface between two planar entities.
   * @param result [out] Result of test
   * @param a First planar entity
   * @param b Second planar entity
   */
  void InterfaceDetection::PlanePlane(bool &result, const PlanarEntity &a,
                                      const PlanarEntity &b)
  {
    result = (a.position() == b.position());
  }

  /**
   * @brief Tests for interface between a spherical entitity and a planar
   * entity.
   * @param result [out] Result of test
   * @param a Spherical entity
   * @param b Planar entity
   */
  void InterfaceDetection::SpherePlane(bool &result, const SphericalEntity &a,
                                       const PlanarEntity &b)
  {
    result = (Vector2::dot(b.normal(), a.position()) + b.position().length() <
              a.radius());
  }
}
}