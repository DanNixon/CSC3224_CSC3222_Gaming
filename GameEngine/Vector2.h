#pragma once

#include <iostream>

class Vector2
{
public:
  Vector2()
      : m_x(0.0)
      , m_y(0.0)
  {
  }

  Vector2(const float x, const float y)
      : m_x(x)
      , m_y(y)
  {
  }

  ~Vector2()
  {
  }

  inline void toZero()
  {
    m_x = 0;
    m_y = 0;
  }

  inline float length2() const
  {
    return m_x * m_x + m_y * m_y;
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
    }
  }

  inline void invert()
  {
    m_x = -m_x;
    m_y = -m_y;
  }

  inline Vector2 inverse() const
  {
    Vector2 i(-m_x, -m_y);
    return i;
  }

  inline Vector2 operator+(const Vector2 &rhs) const
  {
    return Vector2(m_x + rhs.m_x, m_y + rhs.m_y);
  }

  inline Vector2 &operator+=(const Vector2 &rhs)
  {
    m_x += rhs.m_x;
    m_y += rhs.m_y;

    return *this;
  }

  inline Vector2 operator-(const Vector2 &rhs) const
  {
    return Vector2(m_x - rhs.m_x, m_y - rhs.m_y);
  }

  inline Vector2 &operator-=(const Vector2 &rhs)
  {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;

    return *this;
  }

  inline Vector2 operator-() const
  {
    return Vector2(-m_x, -m_y);
  }

  inline Vector2 operator*(const Vector2 &rhs) const
  {
    return Vector2(m_x * rhs.m_x, m_y * rhs.m_y);
  }

  inline Vector2 operator*(float a) const
  {
    return Vector2(m_x * a, m_y * a);
  }

  inline Vector2 operator/(const Vector2 &rhs) const
  {
    return Vector2(m_x / rhs.m_x, m_y / rhs.m_y);
  }

  inline Vector2 operator/(float a) const
  {
    return Vector2(m_x / a, m_y / a);
  }

  inline bool operator==(const Vector2 &other) const
  {
    return (m_x == other.m_x) && (m_y == other.m_y);
  }

  inline bool operator!=(const Vector2 &other) const
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
    default:
      throw new std::runtime_error(
          "Index out of range when selecting a reference to retrun");
    }
  }

  inline friend std::ostream &operator<<(std::ostream &o, const Vector2 &v)
  {
    o << "Vector2(" << v.m_x << "," << v.m_y << ")" << std::endl;
    return o;
  }

private:
  float m_x;
  float m_y;
};
