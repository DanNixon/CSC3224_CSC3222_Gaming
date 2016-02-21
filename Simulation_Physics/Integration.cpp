/**
 * @file
 * @author Dan Nixon
 */

#include "Integration.h"

#include <Vector3.h>

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{
  /**
   * @brief Performs Euler integration.
   * @param out [out] Integral
   * @param x Current value
   * @param y Change value
   * @param dT Time step
   *
   * Performs either explicit, semi-implicit or implicit integration depending
   * on
   * the values of x and y.
   *
   * In all cases x is the current value.
   *
   * For explicit Euler y is the current change value, for implicit Euler y is
   * the next change value.
   */
  void Integration::Euler(Vector3 &out, const Vector3 &x, const Vector3 &y,
                          float dT)
  {
    out = x + (y * dT);
  }
}
}
