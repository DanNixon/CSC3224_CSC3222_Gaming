/**
 * @file
 * @author Dan Nixon
 */

#include "Random.h"

#include <chrono>
#include <iostream>
#include <vector>

#include "Distributions.h"
#include "ProbabilityDistribution.h"
#include "StringUtils.h"

namespace Engine
{
namespace Utility
{
  Random::Random(const std::string &function)
  {
    // Create generator
    unsigned long seed = static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count());
    m_generator = std::mt19937(seed);

    // Parse options
    std::string distribution;
    std::map<std::string, float> params;

    std::vector<std::string> options = StringUtils::Split(function, ',');
    for (auto it = options.begin(); it != options.end(); ++it)
    {
      std::vector<std::string> optionParts = StringUtils::Split(*it, '=');

      std::string optionName = StringUtils::Trim(optionParts[0]);
      std::string optionValue = StringUtils::Trim(optionParts[1]);

      if (optionName == "function")
        distribution = optionValue;
      else
        params[optionName] = std::stof(optionValue);
    }

    // Create the distribution
    if (distribution == "Gaussian")
      m_distribution = new Gaussian(params);
    else if (distribution == "ExpDecay")
      m_distribution = new ExpDecay(params);
    else if (distribution == "ChiSq")
      m_distribution = new ChiSq(params);
    else
      throw std::runtime_error("Unknown distribution");
  }

  Random::~Random()
  {
    delete m_distribution;
  }

  float Random::operator()()
  {
    return m_distribution->next(this);
  }
}
}
