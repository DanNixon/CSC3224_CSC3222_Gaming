/**
 * @file
 * @author Rich Davison, Dan Nixon
 */

#include "Matrix3.h"

/**
 * @brief Creates a matrix with default values (identity).
 */
Matrix3::Matrix3()
{
  toIdentity();
}

/**
 * @brief Creates a new matrix with given values.
 * @param elements Component values
 */
Matrix3::Matrix3(float elements[16])
{
  m_values[0] = elements[0];
  m_values[1] = elements[1];
  m_values[2] = elements[2];

  m_values[3] = elements[4];
  m_values[4] = elements[5];
  m_values[5] = elements[6];

  m_values[6] = elements[8];
  m_values[7] = elements[9];
  m_values[8] = elements[10];
}

/**
 * @brief Creates a new 3x3 matrix from a 4x4 matrix.
 * @param m4 4x4 matrix to copy values from
 */
Matrix3::Matrix3(const Matrix4 &m4)
{
  m_values[0] = m4.m_values[0];
  m_values[1] = m4.m_values[1];
  m_values[2] = m4.m_values[2];

  m_values[3] = m4.m_values[4];
  m_values[4] = m4.m_values[5];
  m_values[5] = m4.m_values[6];

  m_values[6] = m4.m_values[8];
  m_values[7] = m4.m_values[9];
  m_values[8] = m4.m_values[10];
}

Matrix3::~Matrix3()
{
}

/**
 * @brief Sets each component of the matrix to zero.
 */
void Matrix3::toZero()
{
  for (int i = 0; i < 9; ++i)
    m_values[i] = 0.0f;
}

/**
 * @brief Sets the matrix to an identity matrix.
 */
void Matrix3::toIdentity()
{
  toZero();

  m_values[0] = 1.0f;
  m_values[4] = 1.0f;
  m_values[8] = 1.0f;
}

/**
 * @brief Creates a rotation matrix that rotates by 'degrees' around the 'axis'.
 * @param degrees Degrees of rotation
 * @param inaxis Axis to rotate around
 * @return Rotation matrix
 *
 * Analogous to glRotatef().
 */
Matrix3 Matrix3::Rotation(float degrees, const Vector3 &inaxis)
{
  Matrix3 m;

  Vector3 axis = inaxis;

  axis.normalise();

  float c = cos((float)DegToRad(degrees));
  float s = sin((float)DegToRad(degrees));

  m.m_values[0] = (axis.m_x * axis.m_x) * (1.0f - c) + c;
  m.m_values[1] = (axis.m_y * axis.m_x) * (1.0f - c) + (axis.m_z * s);
  m.m_values[2] = (axis.m_z * axis.m_x) * (1.0f - c) - (axis.m_y * s);

  m.m_values[3] = (axis.m_x * axis.m_y) * (1.0f - c) - (axis.m_z * s);
  m.m_values[4] = (axis.m_y * axis.m_y) * (1.0f - c) + c;
  m.m_values[5] = (axis.m_z * axis.m_y) * (1.0f - c) + (axis.m_x * s);

  m.m_values[6] = (axis.m_x * axis.m_z) * (1.0f - c) + (axis.m_y * s);
  m.m_values[7] = (axis.m_y * axis.m_z) * (1.0f - c) - (axis.m_x * s);
  m.m_values[8] = (axis.m_z * axis.m_z) * (1.0f - c) + c;

  return m;
}

/**
 * @brief Creates a scaling matrix (puts the 'scale' vector down the diagonal).
 * @param scale Scale factors in each axis
 * @return Scaling matrix
 *
 * Analogous to glScalef().
 */
Matrix3 Matrix3::Scale(const Vector3 &scale)
{
  Matrix3 m;

  m.m_values[0] = scale.m_x;
  m.m_values[4] = scale.m_y;
  m.m_values[8] = scale.m_z;

  return m;
}
