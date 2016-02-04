/******************************************************************************
Class:Matrix4
Implements:
Author:Rich Davison
Description:VERY simple 4 by 4 matrix class. Students are encouraged to modify
this as necessary! Overloading the [] operator to allow acces to the values
array in a neater way might be a good start, as the floats that make the matrix
up are currently public.

-_-_-_-_-_-_-_,------,
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""

*/ /////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include "common.h"
#include "Vector3.h"
#include "Vector4.h"

class Vector3;

class Matrix4
{
public:
  Matrix4();
  Matrix4(float elements[16]);
  ~Matrix4();

  // Set all matrix values to zero
  void toZero();

  // Sets matrix to identity matrix (1.0 down the diagonal)
  void toIdentity();

  void setRow(unsigned int row, const Vector4 &val)
  {
    if (row <= 3)
    {
      int start = 4 * row;

      m_values[start += 4] = val.m_x;
      m_values[start += 4] = val.m_y;
      m_values[start += 4] = val.m_z;
      m_values[start += 4] = val.m_w;
    }
  }

  void setColumn(unsigned int column, const Vector4 &val)
  {
    if (column <= 3)
    {
      memcpy(&m_values[4 * column], &val, sizeof(Vector4));
    }
  }

  Vector4 row(unsigned int row)
  {
    Vector4 out(0, 0, 0, 1);
    if (row <= 3)
    {
      int start = 4 * row;

      out.m_x = m_values[start += 4];
      out.m_y = m_values[start += 4];
      out.m_z = m_values[start += 4];
      out.m_w = m_values[start += 4];
    }
    return out;
  }

  Vector4 column(unsigned int column)
  {
    Vector4 out(0, 0, 0, 1);

    if (column <= 3)
    {
      memcpy(&out, &m_values[4 * column], sizeof(Vector4));
    }

    return out;
  }

  // Gets the OpenGL position vector (floats 12,13, and 14)
  Vector3 positionVector() const;

  // Sets the OpenGL position vector (floats 12,13, and 14)
  void setPositionVector(const Vector3 in);

  // Gets the scale vector (floats 1,5, and 10)
  Vector3 scalingVector() const;

  // Sets the scale vector (floats 1,5, and 10)
  void setScalingVector(const Vector3 &in);

  // Creates a rotation matrix that rotates by 'degrees' around the 'axis'
  // Analogous to glRotatef
  static Matrix4 Rotation(float degrees, const Vector3 &axis);

  // Creates a scaling matrix (puts the 'scale' vector down the diagonal)
  // Analogous to glScalef
  static Matrix4 Scale(const Vector3 &scale);

  // Creates a translation matrix (identity, with 'translation' vector at
  // floats 12, 13, and 14. Analogous to glTranslatef
  static Matrix4 Translation(const Vector3 &translation);

  // Creates a perspective matrix, with 'znear' and 'zfar' as the near and
  // far planes, using 'aspect' and 'fov' as the aspect ratio and vertical
  // field of vision, respectively.
  static Matrix4 Perspective(float znear, float zfar, float aspect, float fov);

  // Creates an orthographic matrix with 'znear' and 'zfar' as the near and
  // far planes, and so on. Descriptive variable names are a good thing!
  static Matrix4 Orthographic(float znear, float zfar, float right, float left,
                              float top, float bottom);

  // Builds a view matrix suitable for sending straight to the vertex shader.
  // Puts the camera at 'from', with 'lookingAt' centered on the screen, with
  //'up' as the...up axis (pointing towards the top of the screen)
  static Matrix4 BuildViewMatrix(const Vector3 &from, const Vector3 &lookingAt,
                                 const Vector3 up = Vector3(0, 1, 0));

  // Multiplies 'this' matrix by matrix 'a'. Performs the multiplication in
  // 'OpenGL' order (ie, backwards)
  inline Matrix4 operator*(const Matrix4 &a) const
  {
    Matrix4 out;
    // Students! You should be able to think up a really easy way of speeding
    // this up...
    for (unsigned int r = 0; r < 4; ++r)
    {
      for (unsigned int c = 0; c < 4; ++c)
      {
        out.m_values[c + (r * 4)] = 0.0f;
        for (unsigned int i = 0; i < 4; ++i)
        {
          out.m_values[c + (r * 4)] +=
            m_values[c + (i * 4)] * a.m_values[(r * 4) + i];
        }
      }
    }
    return out;
  }

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

  inline Vector4 operator*(const Vector4 &v) const
  {
    return Vector4(
      v.m_x * m_values[0] + v.m_y * m_values[4] + v.m_z * m_values[8] + v.m_w * m_values[12],
      v.m_x * m_values[1] + v.m_y * m_values[5] + v.m_z * m_values[9] + v.m_w * m_values[13],
      v.m_x * m_values[2] + v.m_y * m_values[6] + v.m_z * m_values[10] + v.m_w * m_values[14],
      v.m_x * m_values[3] + v.m_y * m_values[7] + v.m_z * m_values[11] +
      v.m_w * m_values[15]);
  };

  inline friend std::ostream &operator<<(std::ostream &o, const Matrix4 &m)
  {
    o << "Mat4(";
    o << "\t" << m.m_values[0] << "," << m.m_values[4] << "," << m.m_values[8] << "," << m.m_values[12] << std::endl;
    o << "\t\t" << m.m_values[1] << "," << m.m_values[5] << "," << m.m_values[9] << "," << m.m_values[13] << std::endl;
    o << "\t\t" << m.m_values[2] << "," << m.m_values[6] << "," << m.m_values[10] << "," << m.m_values[14] << std::endl;
    o << "\t\t" << m.m_values[3] << "," << m.m_values[7] << "," << m.m_values[11] << "," << m.m_values[15] << " )" << std::endl;
    return o;
  }

private:
  friend class Matrix3;

  float m_values[16];
};
