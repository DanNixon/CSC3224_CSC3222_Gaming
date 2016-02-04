#include "Matrix4.h"

Matrix4::Matrix4()
{
  toIdentity();
}

Matrix4::Matrix4(float elements[16])
{
  memcpy(this->m_values, elements, 16 * sizeof(float));
}

Matrix4::~Matrix4()
{
  toIdentity();
}

void Matrix4::toIdentity()
{
  toZero();
  m_values[0] = 1.0f;
  m_values[5] = 1.0f;
  m_values[10] = 1.0f;
  m_values[15] = 1.0f;
}

void Matrix4::toZero()
{
  for (int i = 0; i < 16; i++)
    m_values[i] = 0.0f;
}

Vector3 Matrix4::positionVector() const
{
  return Vector3(m_values[12], m_values[13], m_values[14]);
}

void Matrix4::setPositionVector(const Vector3 in)
{
  m_values[12] = in.m_x;
  m_values[13] = in.m_y;
  m_values[14] = in.m_z;
}

Vector3 Matrix4::scalingVector() const
{
  return Vector3(m_values[0], m_values[5], m_values[10]);
}

void Matrix4::setScalingVector(const Vector3 &in)
{
  m_values[0] = in.m_x;
  m_values[5] = in.m_y;
  m_values[10] = in.m_z;
}

Matrix4 Matrix4::Perspective(float znear, float zfar, float aspect, float fov)
{
  Matrix4 m;

  const float h = 1.0f / tan(fov * PI_OVER_360);
  float neg_depth = znear - zfar;

  m.m_values[0] = h / aspect;
  m.m_values[5] = h;
  m.m_values[10] = (zfar + znear) / neg_depth;
  m.m_values[11] = -1.0f;
  m.m_values[14] = 2.0f * (znear * zfar) / neg_depth;
  m.m_values[15] = 0.0f;

  return m;
}

// http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
Matrix4 Matrix4::Orthographic(float znear, float zfar, float right, float left,
                              float top, float bottom)
{
  Matrix4 m;

  m.m_values[0] = 2.0f / (right - left);
  m.m_values[5] = 2.0f / (top - bottom);
  m.m_values[10] = -2.0f / (zfar - znear);

  m.m_values[12] = -(right + left) / (right - left);
  m.m_values[13] = -(top + bottom) / (top - bottom);
  m.m_values[14] = -(zfar + znear) / (zfar - znear);
  m.m_values[15] = 1.0f;

  return m;
}

Matrix4 Matrix4::BuildViewMatrix(const Vector3 &from, const Vector3 &lookingAt,
                                 const Vector3 up /*= Vector3(1,0,0)*/)
{
  Matrix4 r;
  r.setPositionVector(Vector3(-from.m_x, -from.m_y, -from.m_z));

  Matrix4 m;

  Vector3 f = (lookingAt - from);
  f.normalise();

  Vector3 s = Vector3::cross(f, up);
  Vector3 u = Vector3::cross(s, f);

  m.m_values[0] = s.m_x;
  m.m_values[4] = s.m_y;
  m.m_values[8] = s.m_z;

  m.m_values[1] = u.m_x;
  m.m_values[5] = u.m_y;
  m.m_values[9] = u.m_z;

  m.m_values[2] = -f.m_x;
  m.m_values[6] = -f.m_y;
  m.m_values[10] = -f.m_z;

  return m * r;
}

Matrix4 Matrix4::Rotation(float degrees, const Vector3 &inaxis)
{
  Matrix4 m;

  Vector3 axis = inaxis;

  axis.normalise();

  float c = cos((float)DegToRad(degrees));
  float s = sin((float)DegToRad(degrees));

  m.m_values[0] = (axis.m_x * axis.m_x) * (1.0f - c) + c;
  m.m_values[1] = (axis.m_y * axis.m_x) * (1.0f - c) + (axis.m_z * s);
  m.m_values[2] = (axis.m_z * axis.m_x) * (1.0f - c) - (axis.m_y * s);

  m.m_values[4] = (axis.m_x * axis.m_y) * (1.0f - c) - (axis.m_z * s);
  m.m_values[5] = (axis.m_y * axis.m_y) * (1.0f - c) + c;
  m.m_values[6] = (axis.m_z * axis.m_y) * (1.0f - c) + (axis.m_x * s);

  m.m_values[8] = (axis.m_x * axis.m_z) * (1.0f - c) + (axis.m_y * s);
  m.m_values[9] = (axis.m_y * axis.m_z) * (1.0f - c) - (axis.m_x * s);
  m.m_values[10] = (axis.m_z * axis.m_z) * (1.0f - c) + c;

  return m;
}

Matrix4 Matrix4::Scale(const Vector3 &scale)
{
  Matrix4 m;

  m.m_values[0] = scale.m_x;
  m.m_values[5] = scale.m_y;
  m.m_values[10] = scale.m_z;

  return m;
}

Matrix4 Matrix4::Translation(const Vector3 &translation)
{
  Matrix4 m;

  m.m_values[12] = translation.m_x;
  m.m_values[13] = translation.m_y;
  m.m_values[14] = translation.m_z;

  return m;
}
