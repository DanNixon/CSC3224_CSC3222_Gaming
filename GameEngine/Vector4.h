#pragma once

#include <iostream>

class Vector4
{
public:
  Vector4()
      : m_x(0.0)
      , m_y(0.0)
      , m_z(0.0)
      , m_w(0.0)
  {
  }

  Vector4(const float x, const float y, const float z, const float w)
      : m_x(x)
      , m_y(y)
      , m_z(z)
      , m_w(w)
  {
  }

  ~Vector4()
  {
  }

  float x() const
  {
    return m_x;
  }

  float y() const
  {
    return m_y;
  }

  float z() const
  {
    return m_z;
  }

  float w() const
  {
    return m_w;
  }

  inline void toZero()
  {
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_w = 0;
  }

  inline float length2() const
  {
    return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
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
      m_w /= len;
    }
  }

  inline void invert()
  {
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
    m_w = -m_w;
  }

  inline Vector4 inverse() const
  {
    return Vector4(-m_x, -m_y, -m_z, -m_w);
  }

  inline Vector4 operator+(const Vector4 &rhs) const
  {
    return Vector4(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z, m_w + rhs.m_w);
  }

  inline Vector4 &operator+=(const Vector4 &rhs)
  {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    m_z += rhs.m_z;
    m_w += rhs.m_w;

    return *this;
  }

  inline Vector4 operator-(const Vector4 &rhs) const
  {
    return Vector4(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z, m_w - rhs.m_w);
  }

  inline Vector4 &operator-=(const Vector4 &rhs)
  {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
    m_z -= rhs.m_z;
    m_w -= rhs.m_w;

    return *this;
  }

  inline Vector4 operator-() const
  {
    return Vector4(-m_x, -m_y, -m_z, -m_w);
  }

  inline Vector4 operator*(const Vector4 &rhs) const
  {
    return Vector4(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z, m_w * rhs.m_w);
  }

  inline Vector4 operator*(float a) const
  {
    return Vector4(m_x * a, m_y * a, m_z * a, m_w * a);
  }

  inline Vector4 operator/(const Vector4 &rhs) const
  {
    return Vector4(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z, m_w / rhs.m_w);
  }

  inline Vector4 operator/(float a) const
  {
    return Vector4(m_x / a, m_y / a, m_z / a, m_w / a);
  }

  inline bool operator==(const Vector4 &other) const
  {
    return (m_x == other.m_x) && (m_y == other.m_y) && (m_z == other.m_z) &&
           (m_w == other.m_w);
  }

  inline bool operator!=(const Vector4 &other) const
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
    case 3:
      return m_w;
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
    case 3:
      return m_w;
    default:
      throw new std::runtime_error(
          "Index out of range when selecting a reference to retrun");
    }
  }

  inline friend std::ostream &operator<<(std::ostream &o, const Vector4 &v)
  {
    o << "Vector4[" << v.m_x << "," << v.m_y << "," << v.m_z << "," << v.m_w
      << "]";
    return o;
  }

private:
  friend class Matrix4;

  float m_x;
  float m_y;
  float m_z;
  float m_w;
};
