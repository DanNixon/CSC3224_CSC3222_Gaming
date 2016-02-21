/**
 * @file
 * @author Dan Nixon
 */

#pragma once

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
    static void Euler(Engine::Maths::Vector3 &out,
                      const Engine::Maths::Vector3 &x,
                      const Engine::Maths::Vector3 &y, float dT);
  };
}
}
