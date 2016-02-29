/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UTILITY_RANDOM_H_
#define _ENGINE_UTILITY_RANDOM_H_

namespace Engine
{
namespace Utility
{
  /**
   * @class Random
   * @brief Utility class for generating random numbers.
   * @author Dan Nixon
   */
  class Random
  {
  public:
    static float random(float lower, float upper);
  };
}
}

#endif