/**
 * @file
 * @author Dan Nixon
 */

#include "InterfaceDetection.h"

#include "SphericalEntity.h"
#include "PlanarEntity.h"

namespace Simulation
{
  namespace Physics
  {
    bool InterfaceDetection::Detect(const Entity &a, const Entity &b)
    {
      const std::type_info &aType = typeid(a);
      const std::type_info &bType = typeid(b);

      const std::type_info &sphereType = typeid(SphericalEntity);
      const std::type_info &planeType = typeid(PlanarEntity);

      bool retVal = false;

      if (aType == sphereType && bType == sphereType)
        SphereSphere(retVal, static_cast<const SphericalEntity &>(a), static_cast<const SphericalEntity &>(b));
      else if (aType == planeType && bType == planeType)
        PlanePlane(retVal, static_cast<const PlanarEntity &>(a), static_cast<const PlanarEntity &>(b));
      else if (aType == sphereType && bType == planeType)
        SpherePlane(retVal, static_cast<const SphericalEntity &>(a), static_cast<const PlanarEntity &>(b));
      else if (aType == planeType && bType == sphereType)
        SpherePlane(retVal, static_cast<const SphericalEntity &>(b), static_cast<const PlanarEntity &>(a));

      return retVal;
    }

    void InterfaceDetection::SphereSphere(bool &result, const SphericalEntity &a, const SphericalEntity &b)
    {
      // TODO
    }

    void InterfaceDetection::PlanePlane(bool &result, const PlanarEntity &a, const PlanarEntity &b)
    {
      // TODO
    }

    void InterfaceDetection::SpherePlane(bool &result, const SphericalEntity &a, const PlanarEntity &b)
    {
      // TODO
    }
  }
}