/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
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

    /**
     * @brief Gets the generator used.
     * @return Reference to generator
     */
    std::mt19937 &generator()
    {
      return m_generator;
    }

  protected:
    std::mt19937 m_generator;                //!< Random generator
    ProbabilityDistribution *m_distribution; //!< Distribution in use
  };
}
}

#endif
