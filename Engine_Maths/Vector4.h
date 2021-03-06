/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_MATHS_VECTOR4_H_
#define _ENGINE_MATHS_VECTOR4_H_

#include <iostream>

#include "Vector3.h"

namespace Engine
{
namespace Maths
{
  /**
   * @class Vector4
   * @brief Four dimensional vector.
   * @author Dan Nixon
   */
  class Vector4
  {
  public:
    /**
     * @brief Gets the number of dimensions.
     * @return Dimension count
     */
    static size_t Dimensions()
    {
      return 4;
    }

    /**
     * @brief Creates a new vector.
     * @param x X coordinate value (default 0)
     * @param y Y coordinate value (default 0)
     * @param z Z coordinate value (default 0)
     * @param w W coordinate value (default 1)
     */
    Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f)
        : m_x(x)
        , m_y(y)
        , m_z(z)
        , m_w(w)
    {
    }

    /**
     * @brief Create a vector using values of a Vector3.
     * @param vec3 Vector3
     * @param w W component
     */
    Vector4(const Vector3 &vec3, float w = 1.0f)
        : m_x(vec3.m_x)
        , m_y(vec3.m_y)
        , m_z(vec3.m_z)
        , m_w(w)
    {
    }

    ~Vector4()
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
     * @brief Gets the Z coordinate value.
     * @return Z coordinate value
     */
    float z() const
    {
      return m_z;
    }

    /**
     * @brief Gets the W coordinate value.
     * @return W coordinate value
     */
    float w() const
    {
      return m_w;
    }

    /**
     * @brief Sets each coordinate of the vector to zero.
     */
    inline void toZero()
    {
      m_x = 0;
      m_y = 0;
      m_z = 0;
      m_w = 0;
    }

    /**
     * @brief Gets the squared length of the vector.
     * @return Length squared
     */
    inline float length2() const
    {
      return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
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
      m_z = -m_z;
      m_w = -m_w;
    }

    /**
     * @brief Returns a negated copy of this vector.
     * @return Inverse vector
     */
    inline Vector4 operator-() const
    {
      return Vector4(-m_x, -m_y, -m_z, -m_w);
    }

    /**
     * @brief Adds another vector to this vector.
     * @param rhs Vector to add
     * @return Result
     */
    inline Vector4 operator+(const Vector4 &rhs) const
    {
      return Vector4(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z, m_w + rhs.m_w);
    }

    /**
     * @brief Adds another vector to this vector.
     * @param rhs Vector to add
     * @return This vector
     */
    inline Vector4 &operator+=(const Vector4 &rhs)
    {
      m_x += rhs.m_x;
      m_y += rhs.m_y;
      m_z += rhs.m_z;
      m_w += rhs.m_w;

      return *this;
    }

    /**
     * @brief Subtracts another vector to this vector.
     * @param rhs Vector to subtract
     * @return Result
     */
    inline Vector4 operator-(const Vector4 &rhs) const
    {
      return Vector4(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z, m_w - rhs.m_w);
    }

    /**
     * @brief Subtracts another vector to this vector.
     * @param rhs Vector to subtract
     * @return This vector
     */
    inline Vector4 &operator-=(const Vector4 &rhs)
    {
      m_x -= rhs.m_x;
      m_y -= rhs.m_y;
      m_z -= rhs.m_z;
      m_w -= rhs.m_w;

      return *this;
    }

    /**
     * @brief Multiplies components of this vector with another.
     * @param rhs Vector to multiply by
     * @return Result
     */
    inline Vector4 operator*(const Vector4 &rhs) const
    {
      return Vector4(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z, m_w * rhs.m_w);
    }

    /**
     * @brief Multiplies components of this vector by a scalar.
     * @param a Scalar to multiply by
     * @return Result
     */
    inline Vector4 operator*(float a) const
    {
      return Vector4(m_x * a, m_y * a, m_z * a, m_w * a);
    }

    /**
     * @brief Multiplies components of this vector by a scalar.
     * @param a Scalar to multiply by
     * @return This vector
     */
    inline Vector4 &operator*=(float a)
    {
      m_x *= a;
      m_y *= a;
      m_z *= a;
      m_w *= a;

      return *this;
    }

    /**
     * @brief Divides components of this vector by another.
     * @param rhs Vector to divide by
     * @return Result
     */
    inline Vector4 operator/(const Vector4 &rhs) const
    {
      return Vector4(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z, m_w / rhs.m_w);
    }

    /**
     * @brief Divides components of this vector by a scalar.
     * @param a Scalar to divide by
     * @return Result
     */
    inline Vector4 operator/(float a) const
    {
      return Vector4(m_x / a, m_y / a, m_z / a, m_w / a);
    }

    /**
     * @brief Tests for equality between this vector and another.
     * @param other Other vector to test
     * @return True if all components are equal
     */
    inline bool operator==(const Vector4 &other) const
    {
      return (m_x == other.m_x) && (m_y == other.m_y) && (m_z == other.m_z) && (m_w == other.m_w);
    }

    /**
     * @brief Tests for inequality between this vector and another.
     * @param other Other vector to test
     * @return True if at least one component differs
     */
    inline bool operator!=(const Vector4 &other) const
    {
      return !(this->operator==(other));
    }

    /**
     * @brief Performs less than test on two vectors.
     * @param other Vector to test against
     * @return True if all elements of this vector are less than corresponding elements of other
     */
    inline bool operator<(const Vector4 &other) const
    {
      return m_x < other.m_x && m_y < other.m_y && m_z < other.m_z && m_w < other.m_w;
    }

    /**
     * @brief Performs less than or equal to test on two vectors.
     * @param other Vector to test against
     * @return True if all elements of this vector are less than or equal to corresponding elements of other
     */
    inline bool operator<=(const Vector4 &other) const
    {
      return m_x <= other.m_x && m_y <= other.m_y && m_z <= other.m_z && m_w <= other.m_w;
    }

    /**
     * @brief Performs greater than test on two vectors.
     * @param other Vector to test against
     * @return True if all elements of this vector are greater than corresponding elements of other
     */
    inline bool operator>(const Vector4 &other) const
    {
      return m_x > other.m_x && m_y > other.m_y && m_z > other.m_z && m_w > other.m_w;
    }

    /**
     * @brief Performs greater than or equal to test on two vectors.
     * @param other Vector to test against
     * @return True if all elements of this vector are greater than or equal to corresponding elements of other
     */
    inline bool operator>=(const Vector4 &other) const
    {
      return m_x >= other.m_x && m_y >= other.m_y && m_z >= other.m_z && m_w >= other.m_w;
    }

    /**
     * @brief Returns the value of a component of the vector.
     * @param i Index of component to return
     * @return Value of component
     */
    inline float operator[](size_t i) const
    {
      switch (i)
      {
      case 0:
        return m_x;
      case 1:
        return m_y;
      case 2:
        return m_z;
      case 3:
        return m_w;
      default:
        return 0.0;
      }
    }

    /**
     * @brief Returns a reference to a component of the vector.
     * @param i Index of component to return
     * @return Reference to component
     */
    inline float &operator[](size_t i)
    {
      switch (i)
      {
      case 0:
        return m_x;
      case 1:
        return m_y;
      case 2:
        return m_z;
      case 3:
        return m_w;
      default:
        throw new std::runtime_error("Index out of range when selecting a reference to retrun");
      }
    }

    /**
     * @brief Outputs a Vector3 to a stream.
     * @param o Stream to output to
     * @param v Vector to output
     * @return Reference to stream
     */
    inline friend std::ostream &operator<<(std::ostream &o, const Vector4 &v)
    {
      o << "[" << v.m_x << "," << v.m_y << "," << v.m_z << "," << v.m_w << "]";
      return o;
    }

    /**
     * @brief Populates a Vector4 from a stream.
     * @param stream Stream to populate from
     * @param v Vector to populate
     * @return Reference to stream
     */
    inline friend std::istream &operator>>(std::istream &stream, Vector4 &v)
    {
      const int n = 100;

      float x, y, z, w;

      stream.ignore(n, '[');
      stream >> x;
      stream.ignore(n, ',');
      stream >> y;
      stream.ignore(n, ',');
      stream >> z;
      stream.ignore(n, ',');
      stream >> w;
      stream.ignore(n, ']');

      v = Vector4(x, y, z, w);

      return stream;
    }

  protected:
    friend class Matrix4;

    float m_x; //!< X coordinate
    float m_y; //!< Y coordinate
    float m_z; //!< Z coordinate
    float m_w; //!< W coordinate
  };
}
}

#endif
