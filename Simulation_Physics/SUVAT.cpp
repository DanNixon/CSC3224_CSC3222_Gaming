/**
 * @file
 * @author Dan Nixon
 */

#include "SUVAT.h"

#include <Vector3.h>

using namespace Engine::Maths;

namespace Simulation
{
namespace Physics
{

/**
 * @brief Calculate final velocity.
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
 * @brief Calculate displacement.
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
 * @brief Calculate displacement.
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
 * @brief Calculate final velocity squared.
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
 * @brief Calculate displacement.
 * @param v Final velocity
 * @param t Time
 * @param a Acceleration
 * @return Displacement
 */
float SUVAT::getSfromVTA(float v, float t, float a)
{
  return (v * t) - ((a * t * t) * 0.5f);
}

/**
 * @brief Calculate final velocity.
 * @param u Initial velocity
 * @param a Acceleration
 * @param t Time
 * @return Final velocity
 */
Vector3 SUVAT::getVfromUAT(const Vector3 &u, const Vector3 &a, float &t)
{
  return u + (a * t);
}

/**
 * @brief Calculate displacement.
 * @param u Initial velocity
 * @param a Acceleration
 * @param t Time
 * @return Displacement
 */
Vector3 SUVAT::getSfromUAT(const Vector3 &u, const Vector3 &a, float &t)
{
  return (u * t) + ((a * t * t) * 0.5f);
}

/**
 * @brief Calculate displacement.
 * @param u Initial velocity
 * @param v Final velocity
 * @param t Time
 * @return Displacement
 */
Vector3 SUVAT::getSfromUVT(const Vector3 &u, const Vector3 &v, float &t)
{
  return (u + v) * t * 0.5f;
}

/**
 * @brief Calculate final velocity squared.
 * @param u Initial velocity
 * @param a Acceleration
 * @param s Displacement
 * @return Final velocity squared
 */
Vector3 SUVAT::getV2fromUAS(const Vector3 &u, const Vector3 &a,
                            const Vector3 &s)
{
  return (u * u) + (a * s * 2.0f);
}

/**
 * @brief Calculate displacement.
 * @param v Final velocity
 * @param t Time
 * @param a Acceleration
 * @return Displacement
 */
Vector3 SUVAT::getSfromVTA(const Vector3 &v, const Vector3 &t, const Vector3 &a)
{
  return (v * t) - ((a * t * t) * 0.5f);
}
}
}
