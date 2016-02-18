/**
 * @file
 * @brief Some random variables and functions, for lack of a better place to
 *        put them.
 * @author Rich Davison
 */

#pragma once

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
static inline double RadToDeg(const double rad)
{
  return rad * 180.0 / PI;
};

/**
 * @brief Converts degrees to radians.
 * @param deg Angle in degrees
 * @return Angle in radians
 */
static inline double DegToRad(const double deg)
{
  return deg * PI / 180.0;
};

/**
 * @def max_n
 * @brief Returns the maximum of two numbers.
 */
#define max_n(a, b) (((a) > (b)) ? (a) : (b))

/**
 * @def min_n
 * @brief Returns the minimum of two numbers.
 */
#define min_n(a, b) (((a) < (b)) ? (a) : (b))

/**
 * @typedef uint
 * @brief Unsigned integer
 */
typedef unsigned int uint;
