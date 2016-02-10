/** @file */

#pragma once

#include <cmath>
#include <iostream>

/**
 * @class Vector3
 * @brief Three dimensional vector.
 */
class Vector3
{
public:
  /**
   * @brief Calculates the dot product of two Vector3.
   * @param a LHS vector
   * @param b RHS vector
   * @return Dot product
   */
  static float dot(const Vector3 &a, const Vector3 &b)
  {
    return (a.m_x * b.m_x) + (a.m_y * b.m_y) + (a.m_z * b.m_z);
  }

  /**
   * @brief Calculates the cross product of two Vector3.
   * @param a LHS vector
   * @param b RHS vector
   * @return Cross product
   */
  static Vector3 cross(const Vector3 &a, const Vector3 &b)
  {
    return Vector3((a.m_y * b.m_z) - (a.m_z * b.m_y),
                   (a.m_z * b.m_x) - (a.m_x * b.m_z),
                   (a.m_x * b.m_y) - (a.m_y * b.m_x));
  }

  /**
  * @brief Calculates the distance between two vectors.
  * @param a First vector
  * @param b Second vector
  * @return Distance
  */
  static float distance(const Vector3 &a, const Vector3 &b)
  {
    return (b - a).length();
  }

  /**
  * @brief Calculates the squared distance between two vectors.
  * @param a First vector
  * @param b Second vector
  * @return Distance
  */
  static float distance2(const Vector3 &a, const Vector3 &b)
  {
    return (b - a).length2();
  }

  /**
   * @brief Creates a new vector with default values of [0, 0, 0].
   */
  Vector3()
      : m_x(0.0)
      , m_y(0.0)
      , m_z(0.0)
  {
  }

  /**
   * @brief Creates a new vector with specified values.
   * @param x X coordinate value
   * @param y Y coordinate value
   * @param z Z coordinate value
   */
  Vector3(const float x, const float y, const float z)
      : m_x(x)
      , m_y(y)
      , m_z(z)
  {
  }

  ~Vector3()
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
   * @brief Sets each coordinate of the vector to zero.
   */
  inline void toZero()
  {
    m_x = 0;
    m_y = 0;
    m_z = 0;
  }

  /**
   * @brief Gets the squared length of the vector.
   * @return Length squared
   */
  inline float length2() const
  {
    return m_x * m_x + m_y * m_y + m_z * m_z;
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
   * @brief Normalises a vector to a length of 1.0.
   *
   * Divides each component of the vector by its length.
   */
  inline void normalise()
  {
    float len = length();

    if (len != 0.0)
    {
      m_x /= len;
      m_y /= len;
      m_z /= len;
    }
  }

  /**
   * @brief Negates each coordinate value of the vector.
   */
  inline void invert()
  {
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
  }

  /**
   * @brief Returns a negated copy of this vector.
   * @return Inverse vector
   */
  inline Vector3 operator-() const
  {
    return Vector3(-m_x, -m_y, -m_z);
  }

  /**
   * @brief Adds another vector to this vector.
   * @param rhs Vector to add
   * @return Result
   */
  inline Vector3 operator+(const Vector3 &rhs) const
  {
    return Vector3(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
  }

  /**
   * @brief Adds another vector to this vector.
   * @param rhs Vector to add
   * @return This vector
   */
  inline Vector3 &operator+=(const Vector3 &rhs)
  {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    m_z += rhs.m_z;

    return *this;
  }

  /**
   * @brief Subtracts another vector to this vector.
   * @param rhs Vector to subtract
   * @return Result
   */
  inline Vector3 operator-(const Vector3 &rhs) const
  {
    return Vector3(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
  }

  /**
   * @brief Subtracts another vector to this vector.
   * @param rhs Vector to subtract
   * @return This vector
   */
  inline Vector3 &operator-=(const Vector3 &rhs)
  {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
    m_z -= rhs.m_z;

    return *this;
  }

  /**
   * @brief Multiplies components of this vector with another.
   * @param rhs Vector to multiply by
   * @return Result
   */
  inline Vector3 operator*(const Vector3 &rhs) const
  {
    return Vector3(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z);
  }

  /**
   * @brief Multiplies components of this vector by a scalar.
   * @param a Scalar to multiply by
   * @return Result
   */
  inline Vector3 operator*(float a) const
  {
    return Vector3(m_x * a, m_y * a, m_z * a);
  }

  /**
   * @brief Divides components of this vector by another.
   * @param rhs Vector to divide by
   * @return Result
   */
  inline Vector3 operator/(const Vector3 &rhs) const
  {
    return Vector3(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z);
  }

  /**
   * @brief Divides components of this vector by a scalar.
   * @param a Scalar to divide by
   * @return Result
   */
  inline Vector3 operator/(float a) const
  {
    return Vector3(m_x / a, m_y / a, m_z / a);
  }

  /**
   * @brief Tests for equality between this vector and another.
   * @param other Other vector to test
   * @return True if all components are equal
   */
  inline bool operator==(const Vector3 &other) const
  {
    return (m_x == other.m_x) && (m_y == other.m_y) && (m_z == other.m_z);
  }

  /**
   * @brief Tests for inequality between this vector and another.
   * @param other Other vector to test
   * @return True if at least one component differs
   */
  inline bool operator!=(const Vector3 &other) const
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
    case 2:
      return m_z;
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
    case 2:
      return m_z;
    default:
      throw new std::runtime_error(
          "Index out of range when selecting a reference to retrun");
    }
  }

  /**
   * @brief Outputs a Vector3 to a stream.
   * @param o Stream to output to
   * @param v Vector to output
   * @return Reference to stream
   */
  inline friend std::ostream &operator<<(std::ostream &o, const Vector3 &v)
  {
    o << "[" << v.m_x << "," << v.m_y << "," << v.m_z << "]";
    return o;
  }

  /**
   * @brief Populates a Vector3 from a stream.
   * @param stream Stream to populate from
   * @param v Vector to populate
   * @return Reference to stream
   */
  inline friend std::istream &operator>>(std::istream &stream, Vector3 &v)
  {
    const int n = 100;

    float x, y, z;

    stream.ignore(n, '[');
    stream >> x;
    stream.ignore(n, ',');
    stream >> y;
    stream.ignore(n, ',');
    stream >> z;
    stream.ignore(n, ']');

    v = Vector3(x, y, z);

    return stream;
  }

private:
  friend class Matrix3;
  friend class Matrix4;

  float m_x; //!< X coordinate
  float m_y; //!< Y coordinate
  float m_z; //!< Z coordinate
};
