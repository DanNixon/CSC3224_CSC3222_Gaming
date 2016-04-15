/**
 * @file
 * @author Rich Davison, Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_MATHS_MATRIX4_H_
#define _ENGINE_MATHS_MATRIX4_H_

#include <iostream>

#include <gl/glew.h>

#include "Vector3.h"
#include "Vector4.h"
#include "math_common.h"

namespace Engine
{
namespace Maths
{
  /**
   * @class Matrix4
   * @brief 4x4 dimensional matrix.
   * @author Rich Davison, Dan Nixon
   *
   * Modified from the nclgl library.
   */
  class Matrix4
  {
  public:
    static Matrix4 Rotation(float degrees, const Vector3 &axis);
    static Matrix4 Scale(const Vector3 &scale);
    static Matrix4 Translation(const Vector3 &translation);

    static Matrix4 Perspective(float zNear, float zfar, float aspect, float fov);
    static Matrix4 Orthographic(float zNear, float zfar, float right, float left, float top, float bottom);

    static Matrix4 BuildViewMatrix(const Vector3 &from, const Vector3 &lookingAt, const Vector3 up = Vector3(0, 1, 0));

    Matrix4();
    Matrix4(float elements[16]);
    ~Matrix4();

    void toZero();
    void toIdentity();

    /**
     * @brief Gets a Vector4 containing the values of a given row of the matrix.
     * @param row Row index
     * @return Row as Vector4
     */
    Vector4 row(size_t row)
    {
      Vector4 out;
      if (row <= 3)
      {
        size_t start = row;

        out.m_x = m_values[start];
        out.m_y = m_values[start += 4];
        out.m_z = m_values[start += 4];
        out.m_w = m_values[start += 4];
      }
      return out;
    }

    /**
     * @brief Set a row of the matrix to values given by a Vector4.
     * @param row Row index
     * @param val Values
     */
    void setRow(size_t row, const Vector4 &val)
    {
      if (row <= 3)
      {
        size_t start = row;

        m_values[start] = val.m_x;
        m_values[start += 4] = val.m_y;
        m_values[start += 4] = val.m_z;
        m_values[start += 4] = val.m_w;
      }
    }

    /**
     * @brief Gets a Vector4 containing the values of a given column of the
     *        matrix.
     * @param column Column index
     * @return Column as Vector4
     */
    Vector4 column(size_t column)
    {
      Vector4 out;

      if (column <= 3)
      {
        memcpy(&out, &m_values[4 * column], sizeof(Vector4));
      }

      return out;
    }

    /**
     * @brief Set a column of the matrix to values given by a Vector4.
     * @param column Column index
     * @param val Values
     */
    void setColumn(size_t column, const Vector4 &val)
    {
      if (column <= 3)
      {
        memcpy(&m_values[4 * column], &val, sizeof(Vector4));
      }
    }

    Vector3 positionVector() const;
    void setPositionVector(const Vector3 &position);

    Vector3 scalingVector() const;
    void setScalingVector(const Vector3 &scaling);

    Vector3 leftVector() const;
    Vector3 upVector() const;
    Vector3 facingVector() const;

    /**
     * @brief Multiplies this matrix by another matrix.
     * @param a Matrix to multiply with
     * @return Result
     *
     * Performs the multiplication in OpenGL order (ie, backwards).
     */
    inline Matrix4 operator*(const Matrix4 &a) const
    {
      Matrix4 out;
      // Students! You should be able to think up a really easy way of speeding
      // this up...
      for (size_t r = 0; r < 4; ++r)
      {
        for (size_t c = 0; c < 4; ++c)
        {
          out.m_values[c + (r * 4)] = 0.0f;
          for (size_t i = 0; i < 4; ++i)
          {
            out.m_values[c + (r * 4)] += m_values[c + (i * 4)] * a.m_values[(r * 4) + i];
          }
        }
      }
      return out;
    }

    /**
     * @brief Multiplies this matrix with a Vector3.
     * @param v Vector3 to multiply with
     * @return Result Vector3
     */
    inline Vector3 operator*(const Vector3 &v) const
    {
      Vector3 vec;

      float temp;

      vec.m_x = v.m_x * m_values[0] + v.m_y * m_values[4] + v.m_z * m_values[8] + m_values[12];
      vec.m_y = v.m_x * m_values[1] + v.m_y * m_values[5] + v.m_z * m_values[9] + m_values[13];
      vec.m_z = v.m_x * m_values[2] + v.m_y * m_values[6] + v.m_z * m_values[10] + m_values[14];

      temp = v.m_x * m_values[3] + v.m_y * m_values[7] + v.m_z * m_values[11] + m_values[15];

      vec.m_x = vec.m_x / temp;
      vec.m_y = vec.m_y / temp;
      vec.m_z = vec.m_z / temp;

      return vec;
    };

    /**
     * @brief Outputs this matrix as a column-major GLdouble matrix.
     * @param m [out] Pointer to output matrix
     */
    inline void toGLdoubleMtx(GLdouble *m) const
    {
      for (int i = 0; i < 16; i++)
        m[i] = m_values[i];
    }

    /**
     * @brief Multiplies this matrix with a Vector4.
     * @param v Vector4 to multiply with
     * @return Result Vector4
     */
    inline Vector4 operator*(const Vector4 &v) const
    {
      return Vector4(v.m_x * m_values[0] + v.m_y * m_values[4] + v.m_z * m_values[8] + v.m_w * m_values[12],
                     v.m_x * m_values[1] + v.m_y * m_values[5] + v.m_z * m_values[9] + v.m_w * m_values[13],
                     v.m_x * m_values[2] + v.m_y * m_values[6] + v.m_z * m_values[10] + v.m_w * m_values[14],
                     v.m_x * m_values[3] + v.m_y * m_values[7] + v.m_z * m_values[11] + v.m_w * m_values[15]);
    };

    /**
     * @brief Outputs the values of the matrix to a stream.
     * @param o Stream to output to
     * @param m Matrix to output
     * @return Stream
     */
    inline friend std::ostream &operator<<(std::ostream &o, const Matrix4 &m)
    {
      o << "Mat4["
        << "\t" << m.m_values[0] << "," << m.m_values[4] << "," << m.m_values[8] << "," << m.m_values[12] << std::endl
        << "\t\t" << m.m_values[1] << "," << m.m_values[5] << "," << m.m_values[9] << "," << m.m_values[13] << std::endl
        << "\t\t" << m.m_values[2] << "," << m.m_values[6] << "," << m.m_values[10] << "," << m.m_values[14]
        << std::endl
        << "\t\t" << m.m_values[3] << "," << m.m_values[7] << "," << m.m_values[11] << "," << m.m_values[15] << "]";
      return o;
    }

  private:
    friend class Matrix3;

    float m_values[16]; //!< Matrix values
  };
}
}

#endif
