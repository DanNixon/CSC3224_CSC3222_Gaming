/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UTILITY_RANDOM_H_
#define _ENGINE_UTILITY_RANDOM_H_

#include <random>
#include <string>

namespace Engine
{
namespace Utility
{
  class ProbabilityDistribution;

  /**
   * @class Random
   * @brief Utility class for generating random numbers.
   * @author Dan Nixon
   */
  class Random
  {
  public:
    Random(const std::string &function);
    virtual ~Random();

    float operator()();

    std::mt19937 &generator()
    {
      return m_generator;
    }

  protected:
    std::mt19937 m_generator;
    ProbabilityDistribution *m_distribution;
  };
}
}

#endif