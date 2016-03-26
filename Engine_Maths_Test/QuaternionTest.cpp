/**
 * @file
 * @author Dan Nixon
 */

#include "CppUnitTest.h"

#include <Quaternion.h>
#include <Vector3.h>

/**
 * @def FP_ACC
 * @brief Accuracy for floating point comparison.
 */
#define FP_ACC 0.001f

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
namespace Maths
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(QuaternionTest)
{
public:
  TEST_METHOD(Quaternion_Default)
  {
    Quaternion q;
    Assert::AreEqual(q.real(), 1.0f);
    Assert::AreEqual(q.i(), 0.0f);
    Assert::AreEqual(q.j(), 0.0f);
    Assert::AreEqual(q.k(), 0.0f);
  }

  TEST_METHOD(Quaternion_ConstructReal)
  {
    Quaternion q(5.0f);
    Assert::AreEqual(q.real(), 5.0f);
    Assert::AreEqual(q.i(), 0.0f);
    Assert::AreEqual(q.j(), 0.0f);
    Assert::AreEqual(q.k(), 0.0f);
  }

  TEST_METHOD(Quaternion_ConstructImaginary)
  {
    Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
    Assert::AreEqual(q.real(), 5.0f);
    Assert::AreEqual(q.i(), 2.0f);
    Assert::AreEqual(q.j(), 4.5f);
    Assert::AreEqual(q.k(), 8.9f);
  }

  TEST_METHOD(Quaternion_ConstructRotation)
  {
    Vector3 axis(1.0f, 1.0f, 1.0f);
    Quaternion q(90.0f, axis);
    float c = 1.0f / sqrt(2.0f);
    float s = c / sqrt(3.0f);
    Assert::AreEqual(q.real(), c, FP_ACC);
    Assert::AreEqual(q.i(), s, FP_ACC);
    Assert::AreEqual(q.j(), s, FP_ACC);
    Assert::AreEqual(q.k(), s, FP_ACC);
  }

  TEST_METHOD(Quaternion_Assignment)
  {
    Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
    Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
    q2 = q1;
    Assert::AreEqual(q2.real(), 5.0f);
    Assert::AreEqual(q2.i(), 2.0f);
    Assert::AreEqual(q2.j(), 4.5f);
    Assert::AreEqual(q2.k(), 8.9f);
  }

  TEST_METHOD(Quaternion_Equality)
  {
    Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
    Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
    Quaternion q3(5.0f, 2.0f, 4.5f, 8.9f);

    Assert::IsTrue(q1 == q3);
    Assert::IsTrue(!(q1 == q2));
  }

  TEST_METHOD(Quaternion_Inequality)
  {
    Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
    Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
    Quaternion q3(5.0f, 2.0f, 4.5f, 8.9f);

    Assert::IsTrue(!(q1 != q3));
    Assert::IsTrue(q1 != q2);
  }

  TEST_METHOD(Quaternion_SetReal)
  {
    Quaternion q;
    q.setReal(10.0f);
    Assert::AreEqual(q.real(), 10.0f, FP_ACC);
    Assert::AreEqual(q.i(), 0.0f, FP_ACC);
    Assert::AreEqual(q.j(), 0.0f, FP_ACC);
    Assert::AreEqual(q.k(), 0.0f, FP_ACC);
  }

  TEST_METHOD(Quaternion_SetI)
  {
    Quaternion q;
    q.setI(1.0f);
    Assert::AreEqual(q.real(), 1.0f, FP_ACC);
    Assert::AreEqual(q.i(), 1.0f, FP_ACC);
    Assert::AreEqual(q.j(), 0.0f, FP_ACC);
    Assert::AreEqual(q.k(), 0.0f, FP_ACC);
  }

  TEST_METHOD(Quaternion_SetJ)
  {
    Quaternion q;
    q.setJ(1.0f);
    Assert::AreEqual(q.real(), 1.0f, FP_ACC);
    Assert::AreEqual(q.i(), 0.0f, FP_ACC);
    Assert::AreEqual(q.j(), 1.0f, FP_ACC);
    Assert::AreEqual(q.k(), 0.0f, FP_ACC);
  }

  TEST_METHOD(Quaternion_SetK)
  {
    Quaternion q;
    q.setK(1.0f);
    Assert::AreEqual(q.real(), 1.0f, FP_ACC);
    Assert::AreEqual(q.i(), 0.0f, FP_ACC);
    Assert::AreEqual(q.j(), 0.0f, FP_ACC);
    Assert::AreEqual(q.k(), 1.0f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Magnitude2)
  {
    Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
    float expected = std::pow(11.3340f, 2);
    Assert::AreEqual(q.magnitude2(), expected, FP_ACC);
  }

  TEST_METHOD(Quaternion_Magnitude)
  {
    Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
    Assert::AreEqual(q.magnitude(), 11.3340f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Normalise)
  {
    Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
    Assert::AreEqual(q.magnitude(), 11.3340f, FP_ACC);
    q.normalise();
    Assert::AreEqual(q.magnitude(), 1.0f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Addition)
  {
    Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
    Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
    Quaternion q3 = q1 + q2;
    Assert::AreEqual(q3.real(), 21.0f, FP_ACC);
    Assert::AreEqual(q3.i(), 4.5f, FP_ACC);
    Assert::AreEqual(q3.j(), 12.8f, FP_ACC);
    Assert::AreEqual(q3.k(), 15.6f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Subtraction)
  {
    Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
    Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
    Quaternion q3 = q1 - q2;
    Assert::AreEqual(q3.real(), -11.0f, FP_ACC);
    Assert::AreEqual(q3.i(), -0.5f, FP_ACC);
    Assert::AreEqual(q3.j(), -3.8f, FP_ACC);
    Assert::AreEqual(q3.k(), 2.2f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Multiplicaion)
  {
    Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
    Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
    Quaternion q3 = q1 * q2;
    Assert::AreEqual(q3.real(), -21.98f, FP_ACC);
    Assert::AreEqual(q3.i(), 0.78f, FP_ACC);
    Assert::AreEqual(q3.j(), 122.35f, FP_ACC);
    Assert::AreEqual(q3.k(), 181.25f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Conjugate)
  {
    Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
    Quaternion conj = q.conjugate();
    Assert::AreEqual(conj.real(), 5.0f, FP_ACC);
    Assert::AreEqual(conj.i(), -2.0f, FP_ACC);
    Assert::AreEqual(conj.j(), -4.5f, FP_ACC);
    Assert::AreEqual(conj.k(), -8.9f, FP_ACC);
  }

  TEST_METHOD(Quaternion_IndexOperator)
  {
    Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
    Assert::AreEqual(q[0], 5.0f, FP_ACC);
    Assert::AreEqual(q[1], 2.0f, FP_ACC);
    Assert::AreEqual(q[2], 4.5f, FP_ACC);
    Assert::AreEqual(q[3], 8.9f, FP_ACC);
  }

  TEST_METHOD(Quaternion_IndexOperatorSet)
  {
    Quaternion q;
    q[0] = 5.0f;
    q[1] = 2.0f;
    q[2] = 4.5f;
    q[3] = 8.9f;
    Assert::AreEqual(q[0], 5.0f, FP_ACC);
    Assert::AreEqual(q[1], 2.0f, FP_ACC);
    Assert::AreEqual(q[2], 4.5f, FP_ACC);
    Assert::AreEqual(q[3], 8.9f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Inverse)
  {
    Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
    Quaternion inv = q.inverse();

    Quaternion r = q * inv;

    Assert::AreEqual(r.real(), 1.0f, FP_ACC);
    Assert::AreEqual(r.i(), 0.0f, FP_ACC);
    Assert::AreEqual(r.j(), 0.0f, FP_ACC);
    Assert::AreEqual(r.k(), 0.0f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Rotation90DegY)
  {
    Quaternion q(90.0f, Vector3(0.0f, 1.0f, 0.0f));
    Vector3 v(1.0f, 0.0f, 0.0f);
    v = q.rotateVector(v);
    Assert::AreEqual(v.x(), 0.0f, FP_ACC);
    Assert::AreEqual(v.y(), 0.0f, FP_ACC);
    Assert::AreEqual(v.z(), -1.0f, FP_ACC);
  }

  TEST_METHOD(Quaternion_Rotation45DegZ)
  {
    Quaternion q(45.0f, Vector3(0.0f, 0.0f, 1.0f));
    Vector3 v(1.0f, 0.0f, 0.0f);
    v = q.rotateVector(v);
    const float h = sqrt(2.0f) / 2.0f;
    Assert::AreEqual(v.x(), h, FP_ACC);
    Assert::AreEqual(v.y(), h, FP_ACC);
    Assert::AreEqual(v.z(), 0.0f, FP_ACC);
  }

  TEST_METHOD(Quaternion_RotationMatrix90DegY)
  {
    Quaternion q(90.0f, Vector3(0.0f, 1.0f, 0.0f));

    Matrix4 m = q.rotationMatrix();

    Assert::AreEqual(0.0f, m.row(0)[0], FP_ACC);
    Assert::AreEqual(0.0f, m.row(0)[1], FP_ACC);
    Assert::AreEqual(1.0f, m.row(0)[2], FP_ACC);
    Assert::AreEqual(0.0f, m.row(0)[3], FP_ACC);

    Assert::AreEqual(0.0f, m.row(1)[0], FP_ACC);
    Assert::AreEqual(1.0f, m.row(1)[1], FP_ACC);
    Assert::AreEqual(0.0f, m.row(1)[2], FP_ACC);
    Assert::AreEqual(0.0f, m.row(1)[3], FP_ACC);

    Assert::AreEqual(-1.0f, m.row(2)[0], FP_ACC);
    Assert::AreEqual(0.0f, m.row(2)[1], FP_ACC);
    Assert::AreEqual(0.0f, m.row(2)[2], FP_ACC);
    Assert::AreEqual(0.0f, m.row(2)[3], FP_ACC);

    Assert::AreEqual(0.0f, m.row(3)[0], FP_ACC);
    Assert::AreEqual(0.0f, m.row(3)[1], FP_ACC);
    Assert::AreEqual(0.0f, m.row(3)[2], FP_ACC);
    Assert::AreEqual(1.0f, m.row(3)[3], FP_ACC);
  }

  TEST_METHOD(Quaternion_RotationMatrix45DegZ)
  {
    Quaternion q(45.0f, Vector3(0.0f, 0.0f, 1.0f));

    Matrix4 m = q.rotationMatrix();

    const float theta = DegToRad(45.0f);
    const float s = std::sin(theta);
    const float c = std::cos(theta);

    Assert::AreEqual(c, m.row(0)[0], FP_ACC);
    Assert::AreEqual(-s, m.row(0)[1], FP_ACC);
    Assert::AreEqual(0.0f, m.row(0)[2], FP_ACC);
    Assert::AreEqual(0.0f, m.row(0)[3], FP_ACC);

    Assert::AreEqual(s, m.row(1)[0], FP_ACC);
    Assert::AreEqual(c, m.row(1)[1], FP_ACC);
    Assert::AreEqual(0.0f, m.row(1)[2], FP_ACC);
    Assert::AreEqual(0.0f, m.row(1)[3], FP_ACC);

    Assert::AreEqual(0.0f, m.row(2)[0], FP_ACC);
    Assert::AreEqual(0.0f, m.row(2)[1], FP_ACC);
    Assert::AreEqual(1.0f, m.row(2)[2], FP_ACC);
    Assert::AreEqual(0.0f, m.row(2)[3], FP_ACC);

    Assert::AreEqual(0.0f, m.row(3)[0], FP_ACC);
    Assert::AreEqual(0.0f, m.row(3)[1], FP_ACC);
    Assert::AreEqual(0.0f, m.row(3)[2], FP_ACC);
    Assert::AreEqual(1.0f, m.row(3)[3], FP_ACC);
  }

  TEST_METHOD(Quaternion_StreamOutput)
  {
    Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
    std::stringstream stream;
    stream << q;
    Assert::AreEqual(stream.str(), std::string("[5,2,4.5,8.9]"));
  }

  TEST_METHOD(Quaternion_StreamInput)
  {
    /* Create stream with valid string */
    std::stringstream stream;
    stream << "[5.0,2.0,4.5,8.9]";

    /* Read the stream */
    Quaternion q;
    stream >> q;

    /* Validate results */
    Assert::AreEqual(q.real(), 5.0f);
    Assert::AreEqual(q.i(), 2.0f);
    Assert::AreEqual(q.j(), 4.5f);
    Assert::AreEqual(q.k(), 8.9f);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
