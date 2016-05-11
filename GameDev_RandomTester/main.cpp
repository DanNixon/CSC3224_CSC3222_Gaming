/**
 * @file
 * @author Dan Nixon
 */

#include <iostream>

#include <Engine_Utility/Random.h>

using namespace Engine::Utility;

/**
 * @brief Entry point of the calculator exercise.
 */
int main(int argc, char *argv[])
{
  size_t numberBins = 25;
  size_t numberSelections = 1000000;
  std::string function = "function=Gaussian,width=3,mean=15";

  std::vector<size_t> bins(numberBins, 0);

  Random rand(function);

  for (size_t i = 0; i < numberSelections;)
  {
    size_t binIdx = (size_t)rand();
    if (binIdx >= 0 && binIdx < numberBins)
    {
      bins[binIdx]++;
      i++;
    }
  }

  for (int i = 0; i < numberBins; i++)
    std::cout << i << ": " << bins[i] << std::endl;

  return 0;
}
