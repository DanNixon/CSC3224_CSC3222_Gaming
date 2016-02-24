/**
 * @file
 * @author Dan Nixon
 */

#include "InterfaceDetection.h"

#include <Vector2.h>

#include "SphericalEntity.h"
#include "PlanarEntity.h"

using namespace Engine::Maths;

namespace Simulation
{
  namespace Physics
  {
    bool InterfaceDetection::Detect(const Entity &a, const Entity &b)
    {
      bool retVal = false;

      if (dynamic_cast<const SphericalEntity *>(&a) && dynamic_cast<const SphericalEntity *>(&b))
        SphereSphere(retVal, static_cast<const SphericalEntity &>(a), static_cast<const SphericalEntity &>(b));

      else if (dynamic_cast<const PlanarEntity *>(&a) && dynamic_cast<const PlanarEntity *>(&b))
        PlanePlane(retVal, static_cast<const PlanarEntity &>(a), static_cast<const PlanarEntity &>(b));

      else if (dynamic_cast<const SphericalEntity *>(&a) && dynamic_cast<const PlanarEntity *>(&b))
        SpherePlane(retVal, static_cast<const SphericalEntity &>(a), static_cast<const PlanarEntity &>(b));

      else if (dynamic_cast<const PlanarEntity *>(&a) && dynamic_cast<const SphericalEntity *>(&b))
        SpherePlane(retVal, static_cast<const SphericalEntity &>(b), static_cast<const PlanarEntity &>(a));

      return retVal;
    }

    void InterfaceDetection::SphereSphere(bool &result, const SphericalEntity &a, const SphericalEntity &b)
    {
      float d = Vector2::distance2(a.position(), b.position());
      float r = a.radius() + b.radius();
      r *= r;
      result = (d < r);
    }

    void InterfaceDetection::PlanePlane(bool &result, const PlanarEntity &a, const PlanarEntity &b)
    {
      result = (a.position() == b.position());
    }

    void InterfaceDetection::SpherePlane(bool &result, const SphericalEntity &a, const PlanarEntity &b)
    {
      result = (Vector2::dot(b.normal(), a.position()) + b.position().length() < a.radius());
    }
  }
}