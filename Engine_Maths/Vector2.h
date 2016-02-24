/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <iostream>

namespace Engine
{
namespace Maths
{
  /**
   * @class Vector2
   * @brief Two dimensional vector.
   * @author Dan Nixon
   */
  class Vector2
  {
  public:
    /**
     * @brief Calculates the dot product of two Vector2.
     * @param a LHS vector
     * @param b RHS vector
     * @return Dot product
     */
    static float dot(const Vector2 &a, const Vector2 &b)
    {
      return (a.m_x * b.m_x) + (a.m_y * b.m_y);
    }

    /**
     * @brief Creates a new vector with default values of [0, 0].
     */
    Vector2()
        : m_x(0.0)
        , m_y(0.0)
    {
    }

    /**
     * @brief Creates a new vector with specified values.
     * @param x X coordinate value
     * @param y Y coordinate value
     */
    Vector2(const float x, const float y)
        : m_x(x)
        , m_y(y)
    {
    }

    ~Vector2()
    {
    }

    /**
     * @brief Gets the X coordinate value.
     * @return X coordinate value
     */
    float x() const
    {
      return m_x;
    }

    /**
     * @brief Gets the Y coordinate value.
     * @return Y coordinate value
     */
    float y() const
    {
      return m_y;
    }

    /**
     * @brief Sets each coordinate of the vector to zero.
     */
    inline void toZero()
    {
      m_x = 0;
      m_y = 0;
    }

    /**
     * @brief Gets the squared length of the vector.
     * @return Length squared
     */
    inline float length2() const
    {
      return m_x * m_x + m_y * m_y;
    }

    /**
     * @brief Gets the length of the vector.
     * @return Length
     */
    inline float length() const
    {
      return sqrt(length2());
    }

    /**
     * @brief Negates each coordinate value of the vector.
     */
    inline void invert()
    {
      m_x = -m_x;
      m_y = -m_y;
    }

    /**
     * @brief Returns a negated copy of this vector.
     * @return Inverse vector
     */
    inline Vector2 operator-() const
    {
      return Vector2(-m_x, -m_y);
    }

    /**
     * @brief Adds another vector to this vector.
     * @param rhs Vector to add
     * @return Result
     */
    inline Vector2 operator+(const Vector2 &rhs) const
    {
      return Vector2(m_x + rhs.m_x, m_y + rhs.m_y);
    }

    /**
     * @brief Adds another vector to this vector.
     * @param rhs Vector to add
     * @return This vector
     */
    inline Vector2 &operator+=(const Vector2 &rhs)
    {
      m_x += rhs.m_x;
      m_y += rhs.m_y;

      return *this;
    }

    /**
     * @brief Subtracts another vector to this vector.
     * @param rhs Vector to subtract
     * @return Result
     */
    inline Vector2 operator-(const Vector2 &rhs) const
    {
      return Vector2(m_x - rhs.m_x, m_y - rhs.m_y);
    }

    /**
     * @brief Subtracts another vector to this vector.
     * @param rhs Vector to subtract
     * @return This vector
     */
    inline Vector2 &operator-=(const Vector2 &rhs)
    {
      m_x -= rhs.m_x;
      m_y -= rhs.m_y;

      return *this;
    }

    /**
     * @brief Multiplies components of this vector with another.
     * @param rhs Vector to multiply by
     * @return Result
     */
    inline Vector2 operator*(const Vector2 &rhs) const
    {
      return Vector2(m_x * rhs.m_x, m_y * rhs.m_y);
    }

    /**
     * @brief Multiplies components of this vector by a scalar.
     * @param a Scalar to multiply by
     * @return Result
     */
    inline Vector2 operator*(float a) const
    {
      return Vector2(m_x * a, m_y * a);
    }

    /**
     * @brief Divides components of this vector by another.
     * @param rhs Vector to divide by
     * @return Result
     */
    inline Vector2 operator/(const Vector2 &rhs) const
    {
      return Vector2(m_x / rhs.m_x, m_y / rhs.m_y);
    }

    /**
     * @brief Divides components of this vector by a scalar.
     * @param a Scalar to divide by
     * @return Result
     */
    inline Vector2 operator/(float a) const
    {
      return Vector2(m_x / a, m_y / a);
    }

    /**
     * @brief Tests for equality between this vector and another.
     * @param other Other vector to test
     * @return True if all components are equal
     */
    inline bool operator==(const Vector2 &other) const
    {
      return (m_x == other.m_x) && (m_y == other.m_y);
    }

    /**
     * @brief Tests for inequality between this vector and another.
     * @param other Other vector to test
     * @return True if at least one component differs
     */
    inline bool operator!=(const Vector2 &other) const
    {
      return !(this->operator==(other));
    }

    /**
     * @brief Returns the value of a component of the vector.
     * @param i Index of component to return
     * @return Value of component
     */
    inline float operator[](const int i) const
    {
      switch (i)
      {
      case 0:
        return m_x;
      case 1:
        return m_y;
      default:
        return 0.0;
      }
    }

    /**
     * @brief Returns a reference to a component of the vector.
     * @param i Index of component to return
     * @return Reference to component
     */
    inline float &operator[](const int i)
    {
      switch (i)
      {
      case 0:
        return m_x;
      case 1:
        return m_y;
      default:
        throw new std::runtime_error(
            "Index out of range when selecting a reference to retrun");
      }
    }

    /**
     * @brief Outputs a Vector2 to a stream.
     * @param o Stream to output to
     * @param v Vector to output
     * @return Reference to stream
     */
    inline friend std::ostream &operator<<(std::ostream &o, const Vector2 &v)
    {
      o << "[" << v.m_x << "," << v.m_y << "]";
      return o;
    }

    /**
     * @brief Populates a Vector2 from a stream.
     * @param stream Stream to populate from
     * @param v Vector to populate
     * @return Reference to stream
     */
    inline friend std::istream &operator>>(std::istream &stream, Vector2 &v)
    {
      const int n = 100;

      float x, y;

      stream.ignore(n, '[');
      stream >> x;
      stream.ignore(n, ',');
      stream >> y;
      stream.ignore(n, ']');

      v = Vector2(x, y);

      return stream;
    }

  private:
    float m_x; //!< X coordinate
    float m_y; //!< Y coordinate
  };
}
}
