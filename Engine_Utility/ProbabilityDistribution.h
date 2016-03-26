/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UTILITY_PROBABILITYDISTRIBUTION_H_
#define _ENGINE_UTILITY_PROBABILITYDISTRIBUTION_H_

#include <map>

#include "Random.h"

namespace Engine
{
namespace Utility
{
  /**
   * @class ProbabilityDistribution
   * @brief Class for storing a probability distribution.
   * @author Dan Nixon
   */
  class ProbabilityDistribution
  {
  public:
    ProbabilityDistribution()
    {
    }

    virtual ~ProbabilityDistribution()
    {
    }

    /**
     * @brief Generates a new random float.
     * @param rand Random
     * @return Random float
     */
    virtual float next(Random *rand) = 0;
  };
}
}

#endif
