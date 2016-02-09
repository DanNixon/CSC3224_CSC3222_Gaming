#include "Quaternion.h"

#include <cmath>
#include <stdexcept>
#include "Vector3.h"

/**
 * Construct a quaternion with a default value of 1.
 */
Quaternion::Quaternion()
    : m_w(1.0)
    , m_i(0.0)
    , m_j(0.0)
    , m_k(0.0)
{
}

/**
 * Construct a real valued quaternion.
 *
 * @param w Real value
 */
Quaternion::Quaternion(const float w)
    : m_w(w)
    , m_i(0.0)
    , m_j(0.0)
    , m_k(0.0)
{
}

/**
 * Construct an imaginary valued quaternion.
 *
 * @param w Real value
 * @param i Coefficient of i
 * @param j Coefficient of j
 * @param k Coefficient of k
 */
Quaternion::Quaternion(const float w, const float i, const float j,
                       const float k)
    : m_w(w)
    , m_i(i)
    , m_j(j)
    , m_k(k)
{
}

/**
 * Construct a quaternion to represent a rotation in a given axis.
 *
 * @param angle Angle in degrees.
 * @param axis Vector defining axit to rotate in
 */
Quaternion::Quaternion(const float angle, const Vector3 &axis)
{
  const float DEG_2_RAD = 3.1415 / 180.0;
  m_w = cos(0.5f * angle * DEG_2_RAD);
  const float s = sin(0.5 * angle * DEG_2_RAD);
  Vector3 temp(axis);
  temp.normalise();
  m_i = s * temp.x();
  m_j = s * temp.y();
  m_k = s * temp.z();
}

/**
 * Construct a quaternion using the values of another.
 *
 * @param rhs Quaternion from which to take values
 */
Quaternion::Quaternion(const Quaternion &other)
    : m_w(other.m_w)
    , m_i(other.m_i)
    , m_j(other.m_j)
    , m_k(other.m_k)
{
}

/**
 * Destructor
 */
Quaternion::~Quaternion()
{
}

/**
 * Assign this quaternion the values of another.
 *
 * @param rhs Quaternion from which to take values
 */
void Quaternion::operator=(const Quaternion &rhs)
{
  m_w = rhs.m_w;
  m_i = rhs.m_i;
  m_j = rhs.m_j;
  m_k = rhs.m_k;
}

/**
 * Check for equality between this quaternion and another.
 *
 * @param rhs Other quaternion to compare to
 * @return True of values are equal
 */
bool Quaternion::operator==(const Quaternion &rhs) const
{
  return (m_w == rhs.m_w && m_i == rhs.m_i && m_j == rhs.m_j && m_k == rhs.m_k);
}

/**
 * Check for inequality between this quaternion and another.
 *
 * @param rhs Other quaternion to compare to
 * @return True if values are not equal
 */
bool Quaternion::operator!=(const Quaternion &rhs) const
{
  return !operator==(rhs);
}

/**
 * Sets the real part of the quaternion.
 *
 * @param w Real part
 */
void Quaternion::setReal(float w)
{
  m_w = w;
}

/**
 * Return the real part of the quaternion.
 *
 * @param Real part
 */
float Quaternion::getReal() const
{
  return m_w;
}

/**
 * Sets the i imaginary part of the quaternion.
 *
 * @param i Imaginary part
 */
void Quaternion::setI(float i)
{
  m_i = i;
}

/**
 * Return the i imaginary part of the quaternion.
 *
 * @return Coefficient of i
 */
float Quaternion::getI() const
{
  return m_i;
}

/**
 * Sets the j imaginary part of the quaternion.
 *
 * @param j Imaginary part
 */
void Quaternion::setJ(float j)
{
  m_j = j;
}

/**
 * Return the j imaginary part of the quaternion.
 *
 * @return Coefficient of j
 */
float Quaternion::getJ() const
{
  return m_j;
}

/**
 * Sets the k imaginary part of the quaternion.
 *
 * @param k Imaginary part
 */
void Quaternion::setK(float k)
{
  m_k = k;
}

/**
 * Return the k imaginary part of the quaternion.
 *
 * @return Coefficient of k
 */
float Quaternion::getK() const
{
  return m_k;
}

/**
 * Calculate the magnitude (length) of the quaternion.
 *
 * @return Magnitude
 */
float Quaternion::magnitude() const
{
  return sqrt(m_w * m_w + m_i * m_i + m_j * m_j + m_k * m_k);
}

/**
 * Calculate the sum of two quaternions.
 *
 * @param rhs Quaternion to add to the LHS
 * @return Sum of quaternions
 */
Quaternion Quaternion::operator+(const Quaternion &rhs) const
{
  return Quaternion(m_w + rhs.m_w, m_i + rhs.m_i, m_j + rhs.m_j, m_k + rhs.m_k);
}

/**
 * Subtract two quaternions.
 *
 * @param rhs Quaternion to subtract from the LHS
 * @return Subtraction of quaternions
 */
Quaternion Quaternion::operator-(const Quaternion &rhs) const
{
  return Quaternion(m_w - rhs.m_w, m_i - rhs.m_i, m_j - rhs.m_j, m_k - rhs.m_k);
}

/**
 * Calculate the product of two quaternions.
 *
 * @param rhs Quaternion to multiply by
 * @return Product of quaternions
 */
Quaternion Quaternion::operator*(const Quaternion &rhs) const
{
  float w = m_w * rhs.m_w - m_i * rhs.m_i - m_j * rhs.m_j - m_k * rhs.m_k;
  float i = m_w * rhs.m_i + rhs.m_w * m_i + m_j * rhs.m_k - rhs.m_j * m_k;
  float j = m_w * rhs.m_j + rhs.m_w * m_j - m_i * rhs.m_k + m_k * rhs.m_i;
  float k = m_w * rhs.m_k + rhs.m_w * m_k + m_i * rhs.m_j - rhs.m_i * m_j;

  return Quaternion(w, i, j, k);
}

/**
 * Return elements of the quaternion by index operator.
 *
 * For reading only.
 *
 * @param index Index accessed
 * @param Quaternion component
 */
float Quaternion::operator[](const int index) const
{
  switch(index)
  {
    case 0:
      return m_w;
    case 1:
      return m_i;
    case 2:
      return m_j;
    case 3:
      return m_k;
    default:
      return 0.0f;
  }
}

/**
 * Return elements of the quaternion by index operator.
 *
 * For reading and writing.
 *
 * @param index Index accessed
 * @param Quaternion component
 */
float &Quaternion::operator[](const int index)
{
  switch(index)
  {
    case 0:
      return m_w;
    case 1:
      return m_i;
    case 2:
      return m_j;
    case 3:
      return m_k;
    default:
      throw std::runtime_error("Quaternion index out of range");
  }
}

/**
 * Returns the complex conjugate of this quaternion.
 *
 * @return Complex conjugate
 */
Quaternion Quaternion::conjugate() const
{
  return Quaternion(m_w, -m_i, -m_j, -m_k);
}

/**
 * Compute the inverse of this quaternion.
 *
 * @return Inverse quaternion
 */
Quaternion Quaternion::inverse() const
{
  Quaternion q = conjugate();

  float m = q.magnitude();
  m *= m;

  if (m == 0.0f)
    m = 1.0f;
  else
    m = 1.0f / m;

  return Quaternion(q.m_w * m, q.m_i * m, q.m_j * m, q.m_k * m);
}

/**
 * Rotates a given vector using this quaternion.
 *
 * @param vector Vector to rotate
 * @return Rotated vector
 */
Vector3 Quaternion::rotateVector(const Vector3 &vector) const
{
  const Quaternion inv = inverse();
  Quaternion pos(0.0f, vector.x(), vector.y(), vector.z());
  pos = pos * inv;
  pos = (*this) * pos;
  return Vector3(pos.getI(), pos.getJ(), pos.getK());
}

/**
 * Outputs the component values of a quaternion to a strem in the format
 * "[w,i,j,k]".
 *
 * @param stream The stream to output to
 * @param q The quaternion to output
 */
std::ostream &operator<<(std::ostream &stream, const Quaternion &q)
{
  stream << "[" << q.m_w << "," << q.m_i << "," << q.m_j << "," << q.m_k << "]";
  return stream;
}

/**
 * Reads component values of a quaternion from a stream in format "[w,i,j,k]".
 *
 * @param stream Stream to read from
 * @param q Quaternion to store values in
 */
std::istream &operator>>(std::istream &stream, Quaternion &q)
{
  float w, i, j, k;
  char delim;
  stream >> delim >> w >> delim >> i >> delim >> j >> delim >> k >> delim;
  q = Quaternion(w, i, j, k);
  return stream;
}