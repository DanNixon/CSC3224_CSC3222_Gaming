/**
 * @file
 * @author Dan Nixon
 */

#include "Random.h"

#include <cstdlib>

namespace Engine
{
namespace Utility
{
  /**
   * @brief Generates a random floating point number between two bounds using a
   *        uniform probability distribution.
   * @param lower Lower bound
   * @param upper Upper bound
   * @return Random number
   */
  float Random::random(float lower, float upper)
  {
    float v = (float)rand() / RAND_MAX;
    return lower + (v * (upper - lower));
  }
}
}
