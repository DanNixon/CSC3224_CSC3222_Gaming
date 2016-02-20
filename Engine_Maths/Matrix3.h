/**
 * @file
 * @author Rich Davison, Dan Nixon
 */

#pragma once

#include "Matrix4.h"

namespace Engine
{
namespace Maths
{

/**
 * @class Matrix3
 * @brief 3x3 dimensional matrix.
 * @author Rich Davison, Dan Nixon
 *
 * Modified from the nclgl library.
 */
class Matrix3
{
public:
  static Matrix3 Rotation(float degrees, const Vector3 &axis);
  static Matrix3 Scale(const Vector3 &scale);

  Matrix3();
  Matrix3(float elements[16]);
  Matrix3(const Matrix4 &m4);
  ~Matrix3();

  void toZero();
  void toIdentity();

  /**
   * @brief Gets a Vector3 containing the values of a given row of the matrix.
   * @param row Row index
   * @return Row as Vector3
   */
  Vector3 row(size_t row)
  {
    Vector3 out(0, 0, 0);
    if (row < 3)
    {
      size_t start = 3 * row;

      out.m_x = m_values[start += 3];
      out.m_y = m_values[start += 3];
      out.m_z = m_values[start += 3];
    }
    return out;
  }

  /**
   * @brief Set a row of the matrix to values given by a Vector3.
   * @param row Row index
   * @param val Values
   */
  void setRow(size_t row, const Vector3 &val)
  {
    if (row < 3)
    {
      size_t start = 3 * row;

      m_values[start += 3] = val.m_x;
      m_values[start += 3] = val.m_y;
      m_values[start += 3] = val.m_z;
    }
  }

  /**
   * @brief Gets a Vector3 containing the values of a given column of the
   *        matrix.
   * @param column Column index
   * @return Column as Vector3
   */
  Vector3 column(size_t column)
  {
    Vector3 out(0, 0, 0);

    if (column < 3)
      memcpy(&out, &m_values[3 * column], sizeof(Vector3));

    return out;
  }

  /**
   * @brief Set a column of the matrix to values given by a Vector3.
   * @param column Column index
   * @param val Values
   */
  void setColumn(size_t column, const Vector3 &val)
  {
    if (column < 3)
      memcpy(&m_values[3 * column], &val, sizeof(Vector3));
  }

  /**
   * @brief Gets a Vector3 containing the values of the diagonal values in the
   *        matrix.
   * @return DIagonal as Vector3
   */
  Vector3 diagonal() const
  {
    return Vector3(m_values[0], m_values[4], m_values[8]);
  }

  /**
   * @brief Set diagonal values of the matrix to values given by a Vector3.
   * @param val Values
   */
  void setDiagonal(const Vector3 &val)
  {
    m_values[0] = val.m_x;
    m_values[4] = val.m_y;
    m_values[8] = val.m_z;
  }

  /**
   * @brief Multiplies this matrix with a Vector3.
   * @param v Vector3 to multiply with
   * @return Result Vector3
   */
  inline Vector3 operator*(const Vector3 &v) const
  {
    Vector3 vec;

    vec.m_x = v.m_x * m_values[0] + v.m_y * m_values[3] + v.m_z * m_values[6];
    vec.m_y = v.m_x * m_values[1] + v.m_y * m_values[4] + v.m_z * m_values[7];
    vec.m_z = v.m_x * m_values[2] + v.m_y * m_values[5] + v.m_z * m_values[8];

    return vec;
  };

  /**
   * @brief Outputs the values of the matrix to a stream.
   * @param o Stream to output to
   * @param m Matrix to output
   * @return Stream
   */
  inline friend std::ostream &operator<<(std::ostream &o, const Matrix3 &m)
  {
    o << "Mat3["
      << "\t" << m.m_values[0] << "," << m.m_values[3] << "," << m.m_values[6]
      << std::endl
      << "\t\t" << m.m_values[1] << "," << m.m_values[4] << "," << m.m_values[7]
      << std::endl
      << "\t\t" << m.m_values[2] << "," << m.m_values[5] << "," << m.m_values[8]
      << "]";
    return o;
  }

private:
  float m_values[9]; //!< Matrix values
};
}
}
