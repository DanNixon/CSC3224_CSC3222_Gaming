/**
 * @file
 * @author Dan Nixon
 */

#include "InterfaceDetection.h"

#include <Engine_Maths/Vector2.h>
#include <Engine_Maths/VectorOperations.h>

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
   * known.
   */
  bool InterfaceDetection::Detect(InterfaceDef &interf)
  {
    bool retVal = false;
    Entity *a = interf.m_e1;
    Entity *b = interf.m_e2;

    if (dynamic_cast<const SphericalEntity *>(a) && dynamic_cast<const SphericalEntity *>(b))
    {
      SphereSphere(retVal, interf.m_normal, static_cast<const SphericalEntity *>(a),
                   static_cast<const SphericalEntity *>(b));
    }

    else if (dynamic_cast<const SphericalEntity *>(a) && dynamic_cast<const PlanarEntity *>(b))
    {
      SpherePlane(retVal, interf.m_normal, static_cast<const SphericalEntity *>(a),
                  static_cast<const PlanarEntity *>(b));
      if (interf.swapped())
        interf.m_normal.invert();
    }

    else if (dynamic_cast<const PlanarEntity *>(a) && dynamic_cast<const SphericalEntity *>(b))
    {
      SpherePlane(retVal, interf.m_normal, static_cast<const SphericalEntity *>(b),
                  static_cast<const PlanarEntity *>(a));
      if (interf.swapped())
        interf.m_normal.invert();
    }

    return retVal;
  }

  /**
   * @brief Tests for interface between two spherical entities.
   * @param result [out] Result of test
   * @param a First spherical entity
   * @param b Second spherical entity
   */
  void InterfaceDetection::SphereSphere(bool &result, Vector2 &normal, const SphericalEntity *a,
                                        const SphericalEntity *b)
  {
    float d = VectorOperations::Distance2(a->position(), b->position());
    float r = (a->radius() - a->impactDistance()) + (b->radius() - b->impactDistance());
    r *= r;
    result = (d < r);

    if (result)
      normal = VectorOperations::GetNormalised(a->position() - b->position());
  }

  /**
   * @brief Tests for interface between a spherical entitity and a planar
   *        entity.
   * @param result [out] Result of test
   * @param a Spherical entity
   * @param b Planar entity
   */
  void InterfaceDetection::SpherePlane(bool &result, Vector2 &normal, const SphericalEntity *a, const PlanarEntity *b)
  {
    float d = -Vector2::dot(b->position(), b->normal());
    float v = Vector2::dot(b->normal(), a->position()) + d;
    result = (v < (a->radius() - a->impactDistance()));
    normal = -b->normal();
  }
}
}