#include "SUVAT.h"

/**
 * @brief
 * @param u Initial velocity
 * @param a Acceleration
 * @param t Time
 * @return Final velocity
 */
float SUVAT::getVfromUAT(float u, float a, float t)
{
  return u + (a * t);
}

/**
 * @brief
 * @param u Initial velocity
 * @param a Acceleration
 * @param t Time
 * @return Displacement
 */
float SUVAT::getSfromUAT(float u, float a, float t)
{
  return (u * t) + ((a * t * t) * 0.5f);
}

/**
 * @brief
 * @param u Initial velocity
 * @param v Final velocity
 * @param t Time
 * @return Displacement
 */
float SUVAT::getSfromUVT(float u, float v, float t)
{
  return (u + v) * t * 0.5f;
}

/**
 * @brief
 * @param u Initial velocity
 * @param a Acceleration
 * @param s Displacement
 * @return Final velocity squared
 */
float SUVAT::getV2fromUAS(float u, float a, float s)
{
  return (u * u) + (2.0f * a * s);
}

/**
 * @brief
 * @param v Final velocity
 * @param t Time
 * @param a Acceleration
 * @return Displacement
 */
float SUVAT::getSfromVTA(float v, float t, float a)
{
  return (v * t) - ((a * t * t) * 0.5f);
}
