#pragma once
#include "Matrix4.h"

class Matrix3
{
public:
  Matrix3(void);
  Matrix3(float elements[16]);
  Matrix3(const Matrix4 &m4);

  ~Matrix3(void);

  // Set all matrix values to zero
  void ToZero();
  // Sets matrix to identity matrix (1.0 down the diagonal)
  void ToIdentity();

  void SetRow(unsigned int row, const Vector3 &val)
  {
    if (row < 3)
    {
      int start = 3 * row;

      values[start += 3] = val.m_x;
      values[start += 3] = val.m_y;
      values[start += 3] = val.m_z;
    }
  }

  void SetColumn(unsigned int column, const Vector3 &val)
  {
    if (column < 3)
    {
      memcpy(&values[3 * column], &val, sizeof(Vector3));
    }
  }

  Vector3 GetRow(unsigned int row)
  {
    Vector3 out(0, 0, 0);
    if (row < 3)
    {
      int start = 3 * row;

      out.m_x = values[start += 3];
      out.m_y = values[start += 3];
      out.m_z = values[start += 3];
    }
    return out;
  }

  Vector3 GetColumn(unsigned int column)
  {
    Vector3 out(0, 0, 0);

    if (column < 3)
    {
      memcpy(&out, &values[3 * column], sizeof(Vector3));
    }

    return out;
  }

  Vector3 GetDiagonal() const
  {
    return Vector3(values[0], values[4], values[8]);
  }

  void SetDiagonal(const Vector3 &in)
  {
    values[0] = in.m_x;
    values[4] = in.m_y;
    values[8] = in.m_z;
  }

  inline Vector3 operator*(const Vector3 &v) const
  {
    Vector3 vec;

    vec.m_x = v.m_x * values[0] + v.m_y * values[3] + v.m_z * values[6];
    vec.m_y = v.m_x * values[1] + v.m_y * values[4] + v.m_z * values[7];
    vec.m_z = v.m_x * values[2] + v.m_y * values[5] + v.m_z * values[8];

    return vec;
  };

  // Handy string output for the matrix. Can get a bit messy, but better than
  // nothing!
  inline friend std::ostream &operator<<(std::ostream &o, const Matrix3 &m)
  {
    o << "Mat3(";
    o << "\t" << m.values[0] << "," << m.values[3] << "," << m.values[6]
      << std::endl;
    o << "\t\t" << m.values[1] << "," << m.values[4] << "," << m.values[7]
      << std::endl;
    o << "\t\t" << m.values[2] << "," << m.values[5] << "," << m.values[8]
      << std::endl;
    return o;
  }

  // Creates a rotation matrix that rotates by 'degrees' around the 'axis'
  // Analogous to glRotatef
  static Matrix3 Rotation(float degrees, const Vector3 &axis);

  // Creates a scaling matrix (puts the 'scale' vector down the diagonal)
  // Analogous to glScalef
  static Matrix3 Scale(const Vector3 &scale);

public:
  float values[9];
};
