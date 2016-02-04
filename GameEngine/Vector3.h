#pragma once

#include <cmath>
#include <iostream>

class Vector3
{
public:
  static float dot(const Vector3 &a, const Vector3 &b)
  {
    return (a.m_x * b.m_x) + (a.m_y * b.m_y) + (a.m_z * b.m_z);
  }

  static Vector3 cross(const Vector3 &a, const Vector3 &b)
  {
    return Vector3((a.m_y * b.m_z) - (a.m_z * b.m_y),
                   (a.m_z * b.m_x) - (a.m_x * b.m_z),
                   (a.m_x * b.m_y) - (a.m_y * b.m_x));
  }

  Vector3()
      : m_x(0.0)
      , m_y(0.0)
      , m_z(0.0)
  {
  }

  Vector3(const float x, const float y, const float z)
      : m_x(x)
      , m_y(y)
      , m_z(z)
  {
  }

  ~Vector3()
  {
  }

  inline void toZero()
  {
    m_x = 0;
    m_y = 0;
    m_z = 0;
  }

  inline float length2() const
  {
    return m_x * m_x + m_y * m_y + m_z * m_z;
  }

  inline float length() const
  {
    return sqrt(length2());
  }

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

  inline void invert()
  {
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
  }

  inline Vector3 inverse() const
  {
    return Vector3(-m_x, -m_y, -m_z);
  }

  inline Vector3 operator+(const Vector3 &rhs) const
  {
    return Vector3(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
  }

  inline Vector3 &operator+=(const Vector3 &rhs)
  {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    m_z += rhs.m_z;

    return *this;
  }

  inline Vector3 operator-(const Vector3 &rhs) const
  {
    return Vector3(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
  }

  inline Vector3 &operator-=(const Vector3 &rhs)
  {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
    m_z -= rhs.m_z;

    return *this;
  }

  inline Vector3 operator-() const
  {
    return Vector3(-m_x, -m_y, -m_z);
  }

  inline Vector3 operator*(const Vector3 &rhs) const
  {
    return Vector3(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z);
  }

  inline Vector3 operator*(float a) const
  {
    return Vector3(m_x * a, m_y * a, m_z * a);
  }

  inline Vector3 operator/(const Vector3 &rhs) const
  {
    return Vector3(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z);
  }

  inline Vector3 operator/(float a) const
  {
    return Vector3(m_x / a, m_y / a, m_z / a);
  }

  inline bool operator==(const Vector3 &other) const
  {
    return (m_x == other.m_x) && (m_y == other.m_y) && (m_z == other.m_z)
  }

  inline bool operator!=(const Vector3 &other) const
  {
    return !(this->operator==(other));
  }

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

  inline friend std::ostream &operator<<(std::ostream &o, const Vector3 &v)
  {
    o << "Vector3(" << v.m_x << "," << v.m_y << "," << v.m_z << ")"
      << std::endl;
    return o;
  }

private:
  float m_x;
  float m_y;
  float m_z;
};
