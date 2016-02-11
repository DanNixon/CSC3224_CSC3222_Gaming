#include "Random.h"

#include <cstdlib>

float Random::random(float lower, float upper)
{
  float v = (float)rand() / RAND_MAX;
  return lower + (v * (upper - lower));
}
