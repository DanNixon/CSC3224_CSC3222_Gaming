#pragma once

#include "ProbabilityDistribution.h"

#include <random>

namespace Engine
{
namespace Utility
{
  class Gaussian : public ProbabilityDistribution
  {
  public:
    Gaussian(std::map<std::string, float> params)
        : ProbabilityDistribution(params)
    {
      m_distribution = std::normal_distribution<float>(params["mean"], params["width"]);
    }

    virtual ~Gaussian()
    {
    }

    virtual float next(Random *rand)
    {
      return m_distribution(rand->generator());
    }

  private:
    std::normal_distribution<float> m_distribution;
  };

  class ExpDecay : public ProbabilityDistribution
  {
  public:
    ExpDecay(std::map<std::string, float> params)
        : ProbabilityDistribution(params)
    {
      m_distribution = std::exponential_distribution<float>(params["decay"]);
    }

    virtual ~ExpDecay()
    {
    }

    virtual float next(Random *rand)
    {
      return m_distribution(rand->generator());
    }

  private:
    std::exponential_distribution<float> m_distribution;
  };

  class ChiSq : public ProbabilityDistribution
  {
  public:
    ChiSq(std::map<std::string, float> params)
        : ProbabilityDistribution(params)
    {
      m_distribution = std::chi_squared_distribution<float>(params["dof"]);
    }

    virtual ~ChiSq()
    {
    }

    virtual float next(Random *rand)
    {
      return m_distribution(rand->generator());
    }

  private:
    std::chi_squared_distribution<float> m_distribution;
  };
}
}
