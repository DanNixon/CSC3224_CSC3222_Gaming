/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_MATHS_VECTOROPERATIONS_H_
#define _ENGINE_MATHS_VECTOROPERATIONS_H_

namespace Engine
{
namespace Maths
{
  /**
   * @class VectorOperations
   * @brief Contains common operations to be performed using vectors.
   * @author Dan Nixon
   */
  class VectorOperations
  {
  public:
    /**
     * @brief Calculates the distance between two vectors.
     * @param a First vector
     * @param b Second vector
     * @return Distance
     */
    template <typename T> inline static float Distance(const T &a, const T &b)
    {
      return (b - a).length();
    }

    /**
     * @brief Calculates the squared distance between two vectors.
     * @param a First vector
     * @param b Second vector
     * @return Distance squared
     */
    template <typename T> inline static float Distance2(const T &a, const T &b)
    {
      return (b - a).length2();
    }

    /**
     * @brief Normalises a vector to a length of 1.0.
     * @param a Vector
     * @return Normalised vector
     *
     * Divides each component of the vector by its length.
     */
    template <typename T> inline static T GetNormalised(const T &a)
    {
      float len = a.length();

      if (len != 0.0)
        return a / len;
      else
        return a;
    }

    /**
     * @brief Normalises a vector to a length of 1.0.
     * @param a Vector
     *
     * Divides each component of the vector by its length.
     */
    template <typename T> inline static void Normalise(T &a)
    {
      float len = a.length();

      if (len != 0.0)
        a = a / len;
    }

    /**
     * @brief Projects a vector onto another.
     * @param a Vector to project
     * @param b Vector on which to project
     * @return Vector a projected onto vector b
     */
    template <typename T> inline static T Project(const T &a, const T &b)
    {
      float fact = T::dot(a, b) / T::dot(b, b);
      return b * fact;
    }
  };
}
}

#endif
