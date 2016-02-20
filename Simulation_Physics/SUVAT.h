/**
 * @file
 * @author Dan Nixon
 */

#pragma once

class Vector3;

namespace Simulation
{
namespace Physics
{

/**
 * @class SUVAT
 * @brief Helper class for performing SUVAT euqations.
 * @author Dan Nixon
 */
class SUVAT
{
public:
  static float getVfromUAT(float u, float a, float t);
  static float getSfromUAT(float u, float a, float t);
  static float getSfromUVT(float u, float v, float t);
  static float getV2fromUAS(float u, float a, float s);
  static float getSfromVTA(float v, float t, float a);

  static Vector3 getVfromUAT(const Vector3 &u, const Vector3 &a, float &t);
  static Vector3 getSfromUAT(const Vector3 &u, const Vector3 &a, float &t);
  static Vector3 getSfromUVT(const Vector3 &u, const Vector3 &v, float &t);
  static Vector3 getV2fromUAS(const Vector3 &u, const Vector3 &a,
                              const Vector3 &s);
  static Vector3 getSfromVTA(const Vector3 &v, const Vector3 &t,
                             const Vector3 &a);
};
}
}
