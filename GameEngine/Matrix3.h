#pragma once
#include "Matrix4.h"

class Matrix3
{
public:
  Matrix3();
  Matrix3(float elements[16]);
  Matrix3(const Matrix4 &m4);
  ~Matrix3();

  // Set all matrix values to zero
  void toZero();

  // Sets matrix to identity matrix (1.0 down the diagonal)
  void toIdentity();

  void setRow(unsigned int row, const Vector3 &val)
  {
    if (row < 3)
    {
      int start = 3 * row;

      m_values[start += 3] = val.m_x;
      m_values[start += 3] = val.m_y;
      m_values[start += 3] = val.m_z;
    }
  }

  void setColumn(unsigned int column, const Vector3 &val)
  {
    if (column < 3)
      memcpy(&m_values[3 * column], &val, sizeof(Vector3));
  }

  Vector3 row(unsigned int row)
  {
    Vector3 out(0, 0, 0);
    if (row < 3)
    {
      int start = 3 * row;

      out.m_x = m_values[start += 3];
      out.m_y = m_values[start += 3];
      out.m_z = m_values[start += 3];
    }
    return out;
  }

  Vector3 column(unsigned int column)
  {
    Vector3 out(0, 0, 0);

    if (column < 3)
      memcpy(&out, &m_values[3 * column], sizeof(Vector3));

    return out;
  }

  Vector3 diagonal() const
  {
    return Vector3(m_values[0], m_values[4], m_values[8]);
  }

  void setDiagonal(const Vector3 &in)
  {
    m_values[0] = in.m_x;
    m_values[4] = in.m_y;
    m_values[8] = in.m_z;
  }

  inline Vector3 operator*(const Vector3 &v) const
  {
    Vector3 vec;

    vec.m_x = v.m_x * m_values[0] + v.m_y * m_values[3] + v.m_z * m_values[6];
    vec.m_y = v.m_x * m_values[1] + v.m_y * m_values[4] + v.m_z * m_values[7];
    vec.m_z = v.m_x * m_values[2] + v.m_y * m_values[5] + v.m_z * m_values[8];

    return vec;
  };

  // Handy string output for the matrix. Can get a bit messy, but better than
  // nothing!
  inline friend std::ostream &operator<<(std::ostream &o, const Matrix3 &m)
  {
    o << "Mat3(";
    o << "\t" << m.m_values[0] << "," << m.m_values[3] << "," << m.m_values[6]
      << std::endl;
    o << "\t\t" << m.m_values[1] << "," << m.m_values[4] << "," << m.m_values[7]
      << std::endl;
    o << "\t\t" << m.m_values[2] << "," << m.m_values[5] << "," << m.m_values[8]
      << std::endl;
    return o;
  }

  // Creates a rotation matrix that rotates by 'degrees' around the 'axis'
  // Analogous to glRotatef
  static Matrix3 Rotation(float degrees, const Vector3 &axis);

  // Creates a scaling matrix (puts the 'scale' vector down the diagonal)
  // Analogous to glScalef
  static Matrix3 Scale(const Vector3 &scale);

private:
  float m_values[9];
};
