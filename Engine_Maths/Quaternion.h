/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <iostream>

class Vector3;

namespace Engine
{
namespace Maths
{

/**
 * @class Quaternion
 * @brief Represents a quaternion.
 * @author Dan Nixon
 */
class Quaternion
{
public:
  Quaternion();
  Quaternion(const float w);
  Quaternion(const float w, const float i, const float j, const float k);
  Quaternion(const float angle, const Vector3 &axis);
  Quaternion(const Quaternion &other);
  ~Quaternion();

  void operator=(const Quaternion &rhs);

  bool operator==(const Quaternion &rhs) const;
  bool operator!=(const Quaternion &rhs) const;

  void setReal(float w);
  float getReal() const;

  void setI(float i);
  float getI() const;

  void setJ(float j);
  float getJ() const;

  void setK(float k);
  float getK() const;

  float magnitude() const;

  Quaternion operator+(const Quaternion &rhs) const;
  Quaternion operator-(const Quaternion &rhs) const;
  Quaternion operator*(const Quaternion &rhs) const;

  float operator[](const int index) const;
  float &operator[](const int index);

  Quaternion conjugate() const;
  Quaternion inverse() const;

  Vector3 rotateVector(const Vector3 &vector) const;

  friend std::ostream &operator<<(std::ostream &stream, const Quaternion &q);

private:
  float m_w; //!< Real component
  float m_i; //!< Imaginary I component
  float m_j; //!< Imaginary J component
  float m_k; //!< Imaginary K component
};

std::istream &operator>>(std::istream &stream, Quaternion &q);
}
}
