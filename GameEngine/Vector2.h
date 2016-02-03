#pragma once

#include <iostream>

class Vector2
{
public:

	Vector2()
		: m_x(0.0), m_y(0.0)
	{

	}

  Vector2(const float x, const float y)
	  : m_x(x), m_y(y)
  {
  }

  ~Vector2()
  {
  }

  void toZero()
  {
	  m_x = 0;
	  m_y = 0;
  }

  float length2() const
  {
	  return m_x*m_x + m_y*m_y;
  }

  float length() const
  {
	  return sqrt(length2());
  }

  void invert()
  {
	  m_x = -m_x;
	  m_y = -m_y;
  }

  Vector2 inverse() const
  {
	  Vector2 i(-m_x, -m_y);
	  return i;
  }

  Vector2 operator+(const Vector2 &rhs) const
  {
	  return Vector2(m_x + rhs.m_x, m_y + rhs.m_y);
  }

  Vector2 &operator+=(const Vector2 &rhs)
  {
	  m_x += rhs.m_x;
	  m_y += rhs.m_y;

	  return *this;
  }

  Vector2 operator-(const Vector2 &rhs) const
  {
	  return Vector2(m_x - rhs.m_x, m_y - rhs.m_y);
  }

  Vector2 &operator-=(const Vector2 &rhs)
  {
	  m_x -= rhs.m_x;
	  m_y -= rhs.m_y;

	  return *this;
  }

  Vector2 operator-() const
  {
	  return Vector2(-m_x, -m_y);
  }

  bool operator==(const Vector2 &other) const
  {
	  return (m_x == other.m_x) && (m_y == other.m_y);
  }

  bool operator!=(const Vector2 &other) const
  {
	  return !(this->operator==(other));
  }

  float operator[](const int i) const
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

  float &operator[](const int i)
  {
	  switch (i)
	  {
	  case 0:
		  return m_x;
	  case 1:
		  return m_y;
	  default:
		  throw new std::runtime_error("Index out of range when selecting a reference to retrun");
	  }
  }

private:
	float m_x;
	float m_y;
};
