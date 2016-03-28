/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_MATHS_QUATERNION_H_
#define _ENGINE_MATHS_QUATERNION_H_

#include <iostream>

#include "Matrix4.h"
#include "Vector3.h"

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
    Quaternion(const float pitch, const float roll, const float yaw);
    Quaternion(const Quaternion &other);
    ~Quaternion();

    void operator=(const Quaternion &rhs);

    bool operator==(const Quaternion &rhs) const;
    bool operator!=(const Quaternion &rhs) const;

    /**
     * @brief Return the real part of the quaternion.
     * @return Real part
     */
    inline float real() const
    {
      return m_w;
    }

    /**
     * @brief Return the i imaginary part of the quaternion.
     * @return Coefficient of i
     */
    inline float i() const
    {
      return m_i;
    }

    /**
     * @brief Return the j imaginary part of the quaternion.
     * @return Coefficient of j
     */
    inline float j() const
    {
      return m_j;
    }

    /**
     * @brief Return the k imaginary part of the quaternion.
     * @return Coefficient of k
     */
    inline float k() const
    {
      return m_k;
    }

    void setReal(float w);
    void setI(float i);
    void setJ(float j);
    void setK(float k);

    float magnitude2() const;
    float magnitude() const;

    void normalise();

    Quaternion operator+(const Quaternion &rhs) const;
    Quaternion operator-(const Quaternion &rhs) const;
    Quaternion operator*(const Quaternion &rhs) const;

    float operator[](const int index) const;
    float &operator[](const int index);

    Quaternion conjugate() const;
    Quaternion inverse() const;

    Vector3 rotateVector(const Vector3 &vector) const;
    Matrix4 rotationMatrix() const;

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

#endif