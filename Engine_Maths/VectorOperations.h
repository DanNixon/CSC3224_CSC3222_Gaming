#pragma once

namespace Engine
{
  namespace Maths
  {
    class VectorOperations
    {
    public:
      /**
       * @brief Calculates the distance between two vectors.
       * @param a First vector
       * @param b Second vector
       * @return Distance
       */
      template <typename T>
      inline T distance(const T &a, const T &b)
      {
        return (b - a).length();
      }

      /**
       * @brief Calculates the squared distance between two vectors.
       * @param a First vector
       * @param b Second vector
       * @return Distance squared
       */
      template <typename T>
      inline T distance2(const T &a, const T &b)
      {
        return (b - a).length2();
      }

      /**
       * @brief Normalises a vector to a length of 1.0.
       *
       * Divides each component of the vector by its length.
       */
      template <typename T>
      inline T normalise(const T &a)
      {
        float len = a.length();

        if (len != 0.0)
          return a / len;
        else
          return a;
      }
    };
  }
}