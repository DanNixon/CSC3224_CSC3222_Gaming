/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_PHYSICS_INTEGRATION_H_
#define _SIMULATION_PHYSICS_INTEGRATION_H_

#include <Vector3.h>

namespace Simulation
{
namespace Physics
{
  /**
   * @class Integration
   * @brief Helper class for performing numerical integration.
   * @author Dan Nixon
   */
  class Integration
  {
  public:
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
    template <typename T> inline static void Euler(T &out, const T &x, const T &y, float dT)
    {
      out = x + (y * dT);
    }
  };
}
}

#endif