#include "Matrix4.h"

Matrix4::Matrix4(void)
{
  ToIdentity();
}

Matrix4::Matrix4(float elements[16])
{
  memcpy(this->values, elements, 16 * sizeof(float));
}

Matrix4::~Matrix4(void)
{
  ToIdentity();
}

void Matrix4::ToIdentity()
{
  ToZero();
  values[0] = 1.0f;
  values[5] = 1.0f;
  values[10] = 1.0f;
  values[15] = 1.0f;
}

void Matrix4::ToZero()
{
  for (int i = 0; i < 16; i++)
  {
    values[i] = 0.0f;
  }
}

Vector3 Matrix4::GetPositionVector() const
{
  return Vector3(values[12], values[13], values[14]);
}

void Matrix4::SetPositionVector(const Vector3 in)
{
  values[12] = in.m_x;
  values[13] = in.m_y;
  values[14] = in.m_z;
}

Vector3 Matrix4::GetScalingVector() const
{
  return Vector3(values[0], values[5], values[10]);
}

void Matrix4::SetScalingVector(const Vector3 &in)
{
  values[0] = in.m_x;
  values[5] = in.m_y;
  values[10] = in.m_z;
}

Matrix4 Matrix4::Perspective(float znear, float zfar, float aspect, float fov)
{
  Matrix4 m;

  const float h = 1.0f / tan(fov * PI_OVER_360);
  float neg_depth = znear - zfar;

  m.values[0] = h / aspect;
  m.values[5] = h;
  m.values[10] = (zfar + znear) / neg_depth;
  m.values[11] = -1.0f;
  m.values[14] = 2.0f * (znear * zfar) / neg_depth;
  m.values[15] = 0.0f;

  return m;
}

// http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
Matrix4 Matrix4::Orthographic(float znear, float zfar, float right, float left,
                              float top, float bottom)
{
  Matrix4 m;

  m.values[0] = 2.0f / (right - left);
  m.values[5] = 2.0f / (top - bottom);
  m.values[10] = -2.0f / (zfar - znear);

  m.values[12] = -(right + left) / (right - left);
  m.values[13] = -(top + bottom) / (top - bottom);
  m.values[14] = -(zfar + znear) / (zfar - znear);
  m.values[15] = 1.0f;

  return m;
}

Matrix4 Matrix4::BuildViewMatrix(const Vector3 &from, const Vector3 &lookingAt,
                                 const Vector3 up /*= Vector3(1,0,0)*/)
{
  Matrix4 r;
  r.SetPositionVector(Vector3(-from.m_x, -from.m_y, -from.m_z));

  Matrix4 m;

  Vector3 f = (lookingAt - from);
  f.normalise();

  Vector3 s = Vector3::cross(f, up);
  Vector3 u = Vector3::cross(s, f);

  m.values[0] = s.m_x;
  m.values[4] = s.m_y;
  m.values[8] = s.m_z;

  m.values[1] = u.m_x;
  m.values[5] = u.m_y;
  m.values[9] = u.m_z;

  m.values[2] = -f.m_x;
  m.values[6] = -f.m_y;
  m.values[10] = -f.m_z;

  return m * r;
}

Matrix4 Matrix4::Rotation(float degrees, const Vector3 &inaxis)
{
  Matrix4 m;

  Vector3 axis = inaxis;

  axis.normalise();

  float c = cos((float)DegToRad(degrees));
  float s = sin((float)DegToRad(degrees));

  m.values[0] = (axis.m_x * axis.m_x) * (1.0f - c) + c;
  m.values[1] = (axis.m_y * axis.m_x) * (1.0f - c) + (axis.m_z * s);
  m.values[2] = (axis.m_z * axis.m_x) * (1.0f - c) - (axis.m_y * s);

  m.values[4] = (axis.m_x * axis.m_y) * (1.0f - c) - (axis.m_z * s);
  m.values[5] = (axis.m_y * axis.m_y) * (1.0f - c) + c;
  m.values[6] = (axis.m_z * axis.m_y) * (1.0f - c) + (axis.m_x * s);

  m.values[8] = (axis.m_x * axis.m_z) * (1.0f - c) + (axis.m_y * s);
  m.values[9] = (axis.m_y * axis.m_z) * (1.0f - c) - (axis.m_x * s);
  m.values[10] = (axis.m_z * axis.m_z) * (1.0f - c) + c;

  return m;
}

Matrix4 Matrix4::Scale(const Vector3 &scale)
{
  Matrix4 m;

  m.values[0] = scale.m_x;
  m.values[5] = scale.m_y;
  m.values[10] = scale.m_z;

  return m;
}

Matrix4 Matrix4::Translation(const Vector3 &translation)
{
  Matrix4 m;

  m.values[12] = translation.m_x;
  m.values[13] = translation.m_y;
  m.values[14] = translation.m_z;

  return m;
}
