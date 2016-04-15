/**
 * @file
 * @brief Some random variables and functions, for lack of a better place to
 *        put them.
 * @author Rich Davison
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_MATHS_MATHCOMMON_H_
#define _ENGINE_MATHS_MATHCOMMON_H_

namespace Engine
{
namespace Maths
{
  /**
   * @var PI
   * @brief Is Pi.
   */
  static const float PI = 3.14159265358979323846f;

  /**
   * @var PI_OVER_360
   * @brief Pi / 360.
   */
  static const float PI_OVER_360 = PI / 360.0f;

  /**
   * @brief Converts radians to degrees.
   * @param rad Angle in radians
   * @return Angle in degrees
   */
  static inline float RadToDeg(const float rad)
  {
    return rad * 180.0f / PI;
  };

  /**
   * @brief Converts degrees to radians.
   * @param deg Angle in degrees
   * @return Angle in radians
   */
  static inline float DegToRad(const float deg)
  {
    return deg * PI / 180.0f;
  };
}
}

#endif