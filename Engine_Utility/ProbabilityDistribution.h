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
    ProbabilityDistribution(std::map<std::string, float> params)
    {
    }

    virtual ~ProbabilityDistribution()
    {
    }

    virtual float next(Random *rand) = 0;
  };
}
}

#endif