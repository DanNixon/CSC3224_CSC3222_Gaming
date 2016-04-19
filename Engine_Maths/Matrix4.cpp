/**
 * @file
 * @author Rich Davison, Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "Matrix4.h"

#include "VectorOperations.h"

namespace Engine
{
namespace Maths
{
  /**
   * @brief Creates a matrix with default values (identity).
   */
  Matrix4::Matrix4()
  {
    toIdentity();
  }

  /**
   * @brief Creates a new matrix with given values.
   * @param elements Component values
   */
  Matrix4::Matrix4(float elements[16])
  {
    memcpy(this->m_values, elements, 16 * sizeof(float));
  }

  Matrix4::~Matrix4()
  {
    toIdentity();
  }

  /**
   * @brief Sets each component of the matrix to zero.
   */
  void Matrix4::toZero()
  {
    for (int i = 0; i < 16; i++)
      m_values[i] = 0.0f;
  }

  /**
   * @brief Sets the matrix to an identity matrix.
   */
  void Matrix4::toIdentity()
  {
    toZero();
    m_values[0] = 1.0f;
    m_values[5] = 1.0f;
    m_values[10] = 1.0f;
    m_values[15] = 1.0f;
  }

  /**
   * @brief Extracts the position vector from the matrix.
   * @return Position vector
   */
  Vector3 Matrix4::positionVector() const
  {
    return Vector3(m_values[12], m_values[13], m_values[14]);
  }

  /**
   * @brief Sets the position component of the matrix.
   * @param position Position vector
   */
  void Matrix4::setPositionVector(const Vector3 &position)
  {
    m_values[12] = position.m_x;
    m_values[13] = position.m_y;
    m_values[14] = position.m_z;
  }

  /**
   * @brief Extracts the scaling vector from the matrix.
   * @return Scaling vector
   */
  Vector3 Matrix4::scalingVector() const
  {
    return Vector3(m_values[0], m_values[5], m_values[10]);
  }

  /**
   * @brief Sets the scaling component of the matrix.
   * @param scaling Scaling vector
   */
  void Matrix4::setScalingVector(const Vector3 &scaling)
  {
    m_values[0] = scaling.m_x;
    m_values[5] = scaling.m_y;
    m_values[10] = scaling.m_z;
  }

  /**
   * @brief Extracts the left vector from this matrix.
   * @return Left direction vector
   */
  Vector3 Matrix4::leftVector() const
  {
    return Vector3(m_values[0], m_values[4], m_values[8]);
  }

  /**
   * @brief Extracts the up vector from this matrix.
   * @return Up direction vector
   */
  Vector3 Matrix4::upVector() const
  {
    return Vector3(m_values[1], m_values[5], m_values[9]);
  }

  /**
   * @brief Extracts the facing vector from this matrix.
   * @return Face direction vector
   */
  Vector3 Matrix4::facingVector() const
  {
    return Vector3(m_values[2], m_values[6], m_values[10]);
  }

  /**
   * @brief Creates a perspective matrix,
   * @param zNear Near plane depth
   * @param zFar Far plane depth
   * @param aspect Aspect ratio
   * @param fov Field of vision in degrees
   * @return Perspective matrix
   */
  Matrix4 Matrix4::Perspective(float zNear, float zFar, float aspect, float fov)
  {
    Matrix4 m;

    const float h = 1.0f / tan(fov * PI_OVER_360);
    float neg_depth = zNear - zFar;

    m.m_values[0] = h / aspect;
    m.m_values[5] = h;
    m.m_values[10] = (zFar + zNear) / neg_depth;
    m.m_values[11] = -1.0f;
    m.m_values[14] = 2.0f * (zNear * zFar) / neg_depth;
    m.m_values[15] = 0.0f;

    return m;
  }

  /**
   * @brief Creates an orthographic matrix.
   * @param zNear Near plane depth
   * @param zFar Far plane depth
   * @param right Right plane position
   * @param left Left plane position
   * @param top Top plane position
   * @param bottom Bottom plane position
   * @return Orthographic matrix
   *
   * http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
   */
  Matrix4 Matrix4::Orthographic(float zNear, float zFar, float right, float left, float top, float bottom)
  {
    Matrix4 m;

    m.m_values[0] = 2.0f / (right - left);
    m.m_values[5] = 2.0f / (top - bottom);
    m.m_values[10] = -2.0f / (zFar - zNear);

    m.m_values[12] = -(right + left) / (right - left);
    m.m_values[13] = -(top + bottom) / (top - bottom);
    m.m_values[14] = -(zFar + zNear) / (zFar - zNear);
    m.m_values[15] = 1.0f;

    return m;
  }

  /**
   * @brief Builds a view matrix suitable for sending straight to the vertex
   *        shader.
   * @param from Camera position
   * @param lookingAt Centre position on screen
   * @param up Upwards (top of screen) direction
   * @return View matrix
   */
  Matrix4 Matrix4::BuildViewMatrix(const Vector3 &from, const Vector3 &lookingAt, const Vector3 up)
  {
    Matrix4 r;
    r.setPositionVector(Vector3(-from.m_x, -from.m_y, -from.m_z));

    Matrix4 m;

    Vector3 f = (lookingAt - from);
    VectorOperations::Normalise(f);

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

  /**
   * @brief Creates a rotation matrix that rotates by 'degrees' around the
   * 'axis'.
   * @param degrees Degrees of rotation
   * @param inaxis Axis to rotate around
   * @return Rotation matrix
   *
   * Analogous to glRotatef().
   */
  Matrix4 Matrix4::Rotation(float degrees, const Vector3 &inaxis)
  {
    Matrix4 m;

    Vector3 axis = inaxis;

    VectorOperations::Normalise(axis);

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

  /**
   * @brief Creates a scaling matrix (puts the 'scale' vector down the
   * diagonal).
   * @param scale Scale factors in each axis
   * @return Scaling matrix
   *
   * Analogous to glScalef().
   */
  Matrix4 Matrix4::Scale(const Vector3 &scale)
  {
    Matrix4 m;

    m.m_values[0] = scale.m_x;
    m.m_values[5] = scale.m_y;
    m.m_values[10] = scale.m_z;

    return m;
  }

  /**
  * @brief Creates a scaling matrix with uniform scaling in each axis.
  * @param scale Uniform scaling factor
  * @return Scaling matrix
  */
  Matrix4 Matrix4::Scale(float scale)
  {
    Matrix4 m;

    m.m_values[0] = scale;
    m.m_values[5] = scale;
    m.m_values[10] = scale;

    return m;
  }

  /**
   * @brief Creates a translation matrix.
   * @param translation Vector3 describing translation in each axis
   * @return Translation matrix
   *
   * Identity, with 'translation' vector at floats 12, 13, and 14.
   * Analogous to glTranslatef().
   */
  Matrix4 Matrix4::Translation(const Vector3 &translation)
  {
    Matrix4 m;

    m.m_values[12] = translation.m_x;
    m.m_values[13] = translation.m_y;
    m.m_values[14] = translation.m_z;

    return m;
  }
}
}
