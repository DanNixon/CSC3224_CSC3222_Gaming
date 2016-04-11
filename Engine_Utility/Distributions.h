/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_UTILITY_DISTRIBUTIONS_H_
#define _ENGINE_UTILITY_DISTRIBUTIONS_H_

#include "ProbabilityDistribution.h"

#include <random>

namespace Engine
{
namespace Utility
{
  /**
   * @class Gaussian
   * @brief Probability distribution for the Gaussian distribution.
   * @author Dan Nixon
   */
  class Gaussian : public ProbabilityDistribution
  {
  public:
    /**
     * @brief Creates a new Gausian distribution.
     * @param params Parameters
     *
     * Parameters are:
     *  mean - peak centre
     *  width - standard deviation
     */
    Gaussian(std::map<std::string, float> params)
    {
      m_distribution = std::normal_distribution<float>(params["mean"], params["width"]);
    }

    virtual ~Gaussian()
    {
    }

    /**
     * @copydoc ProbabilityDistribution::next
     */
    virtual float next(Random *rand)
    {
      return m_distribution(rand->generator());
    }

  private:
    std::normal_distribution<float> m_distribution; //!< Probability distribution
  };

  /**
   * @class ExpDecay
   * @brief Probability distribution for an exponential decay function.
   * @author Dan Nixon
   */
  class ExpDecay : public ProbabilityDistribution
  {
  public:
    /**
     * @brief Creates a new exponential decay distribution.
     * @param params Parameters
     *
     * Parameters are:
     *  decay - decay constant
     */
    ExpDecay(std::map<std::string, float> params)
    {
      m_distribution = std::exponential_distribution<float>(params["decay"]);
    }

    virtual ~ExpDecay()
    {
    }

    /**
     * @copydoc ProbabilityDistribution::next
     */
    virtual float next(Random *rand)
    {
      return m_distribution(rand->generator());
    }

  private:
    std::exponential_distribution<float> m_distribution; //!< Probability distribution
  };

  /**
   * @class ChiSq
   * @brief Probability distribution for the Chi-squared distribution.
   * @author Dan Nixon
   */
  class ChiSq : public ProbabilityDistribution
  {
  public:
    /**
     * @brief Creates a new Chi-squared distribution.
     * @param params Parameters
     *
     * Parameters are:
     *  dof - number of degrees of freedom
     */
    ChiSq(std::map<std::string, float> params)
    {
      m_distribution = std::chi_squared_distribution<float>(params["dof"]);
    }

    virtual ~ChiSq()
    {
    }

    /**
     * @copydoc ProbabilityDistribution::next
     */
    virtual float next(Random *rand)
    {
      return m_distribution(rand->generator());
    }

  private:
    std::chi_squared_distribution<float> m_distribution; //!< Probability distribution
  };
}
}

#endif
