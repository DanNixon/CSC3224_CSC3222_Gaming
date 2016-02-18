#include "stdafx.h"
#include "CppUnitTest.h"

#include <Quaternion.h>
#include <Vector3.h>

#define TH 0.001f

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{
TEST_CLASS(QuaternionTest){public : TEST_METHOD(test_Default){Quaternion q;
Assert::AreEqual(q.getReal(), 1.0f);
Assert::AreEqual(q.getI(), 0.0f);
Assert::AreEqual(q.getJ(), 0.0f);
Assert::AreEqual(q.getK(), 0.0f);
}

TEST_METHOD(test_ConstructReal)
{
  Quaternion q(5.0f);
  Assert::AreEqual(q.getReal(), 5.0f);
  Assert::AreEqual(q.getI(), 0.0f);
  Assert::AreEqual(q.getJ(), 0.0f);
  Assert::AreEqual(q.getK(), 0.0f);
}

TEST_METHOD(test_ConstructImaginary)
{
  Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
  Assert::AreEqual(q.getReal(), 5.0f);
  Assert::AreEqual(q.getI(), 2.0f);
  Assert::AreEqual(q.getJ(), 4.5f);
  Assert::AreEqual(q.getK(), 8.9f);
}

TEST_METHOD(test_ConstructRotation)
{
  Vector3 axis(1.0f, 1.0f, 1.0f);
  Quaternion q(90.0f, axis);
  float c = 1.0f / sqrt(2.0f);
  float s = c / sqrt(3.0f);
  Assert::AreEqual(q.getReal(), c, TH);
  Assert::AreEqual(q.getI(), s, TH);
  Assert::AreEqual(q.getJ(), s, TH);
  Assert::AreEqual(q.getK(), s, TH);
}

TEST_METHOD(test_Assignment)
{
  Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
  Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
  q2 = q1;
  Assert::AreEqual(q2.getReal(), 5.0f);
  Assert::AreEqual(q2.getI(), 2.0f);
  Assert::AreEqual(q2.getJ(), 4.5f);
  Assert::AreEqual(q2.getK(), 8.9f);
}

TEST_METHOD(test_Equality)
{
  Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
  Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
  Quaternion q3(5.0f, 2.0f, 4.5f, 8.9f);

  Assert::IsTrue(q1 == q3);
  Assert::IsTrue(!(q1 == q2));
}

TEST_METHOD(test_Inequality)
{
  Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
  Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
  Quaternion q3(5.0f, 2.0f, 4.5f, 8.9f);

  Assert::IsTrue(!(q1 != q3));
  Assert::IsTrue(q1 != q2);
}

TEST_METHOD(test_SetReal)
{
  Quaternion q;
  q.setReal(10.0f);
  Assert::AreEqual(q.getReal(), 10.0f, TH);
  Assert::AreEqual(q.getI(), 0.0f, TH);
  Assert::AreEqual(q.getJ(), 0.0f, TH);
  Assert::AreEqual(q.getK(), 0.0f, TH);
}

TEST_METHOD(test_SetI)
{
  Quaternion q;
  q.setI(1.0f);
  Assert::AreEqual(q.getReal(), 1.0f, TH);
  Assert::AreEqual(q.getI(), 1.0f, TH);
  Assert::AreEqual(q.getJ(), 0.0f, TH);
  Assert::AreEqual(q.getK(), 0.0f, TH);
}

TEST_METHOD(test_SetJ)
{
  Quaternion q;
  q.setJ(1.0f);
  Assert::AreEqual(q.getReal(), 1.0f, TH);
  Assert::AreEqual(q.getI(), 0.0f, TH);
  Assert::AreEqual(q.getJ(), 1.0f, TH);
  Assert::AreEqual(q.getK(), 0.0f, TH);
}

TEST_METHOD(test_SetK)
{
  Quaternion q;
  q.setK(1.0f);
  Assert::AreEqual(q.getReal(), 1.0f, TH);
  Assert::AreEqual(q.getI(), 0.0f, TH);
  Assert::AreEqual(q.getJ(), 0.0f, TH);
  Assert::AreEqual(q.getK(), 1.0f, TH);
}

TEST_METHOD(test_Magnitude)
{
  Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
  Assert::AreEqual(q.magnitude(), 11.3340f, TH);
}

TEST_METHOD(test_Addition)
{
  Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
  Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
  Quaternion q3 = q1 + q2;
  Assert::AreEqual(q3.getReal(), 21.0f, TH);
  Assert::AreEqual(q3.getI(), 4.5f, TH);
  Assert::AreEqual(q3.getJ(), 12.8f, TH);
  Assert::AreEqual(q3.getK(), 15.6f, TH);
}

TEST_METHOD(test_Subtraction)
{
  Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
  Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
  Quaternion q3 = q1 - q2;
  Assert::AreEqual(q3.getReal(), -11.0f, TH);
  Assert::AreEqual(q3.getI(), -0.5f, TH);
  Assert::AreEqual(q3.getJ(), -3.8f, TH);
  Assert::AreEqual(q3.getK(), 2.2f, TH);
}

TEST_METHOD(test_Multiplicaion)
{
  Quaternion q1(5.0f, 2.0f, 4.5f, 8.9f);
  Quaternion q2(16.0f, 2.5f, 8.3f, 6.7f);
  Quaternion q3 = q1 * q2;
  Assert::AreEqual(q3.getReal(), -21.98f, TH);
  Assert::AreEqual(q3.getI(), 0.78f, TH);
  Assert::AreEqual(q3.getJ(), 122.35f, TH);
  Assert::AreEqual(q3.getK(), 181.25f, TH);
}

TEST_METHOD(test_Conjugate)
{
  Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
  Quaternion conj = q.conjugate();
  Assert::AreEqual(conj.getReal(), 5.0f, TH);
  Assert::AreEqual(conj.getI(), -2.0f, TH);
  Assert::AreEqual(conj.getJ(), -4.5f, TH);
  Assert::AreEqual(conj.getK(), -8.9f, TH);
}

TEST_METHOD(test_IndexOperator)
{
  Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
  Assert::AreEqual(q[0], 5.0f, TH);
  Assert::AreEqual(q[1], 2.0f, TH);
  Assert::AreEqual(q[2], 4.5f, TH);
  Assert::AreEqual(q[3], 8.9f, TH);
}

TEST_METHOD(test_IndexOperatorSet)
{
  Quaternion q;
  q[0] = 5.0f;
  q[1] = 2.0f;
  q[2] = 4.5f;
  q[3] = 8.9f;
  Assert::AreEqual(q[0], 5.0f, TH);
  Assert::AreEqual(q[1], 2.0f, TH);
  Assert::AreEqual(q[2], 4.5f, TH);
  Assert::AreEqual(q[3], 8.9f, TH);
}

TEST_METHOD(test_Inverse)
{
  Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
  Quaternion inv = q.inverse();

  Quaternion r = q * inv;

  Assert::AreEqual(r.getReal(), 1.0f, TH);
  Assert::AreEqual(r.getI(), 0.0f, TH);
  Assert::AreEqual(r.getJ(), 0.0f, TH);
  Assert::AreEqual(r.getK(), 0.0f, TH);
}

TEST_METHOD(test_Rotation90DegY)
{
  Quaternion q(90.0f, Vector3(0.0f, 1.0f, 0.0f));
  Vector3 v(1.0f, 0.0f, 0.0f);
  v = q.rotateVector(v);
  Assert::AreEqual(v.x(), 0.0f, TH);
  Assert::AreEqual(v.y(), 0.0f, TH);
  Assert::AreEqual(v.z(), -1.0f, TH);
}

TEST_METHOD(test_Rotation45DegZ)
{
  Quaternion q(45.0f, Vector3(0.0f, 0.0f, 1.0f));
  Vector3 v(1.0f, 0.0f, 0.0f);
  v = q.rotateVector(v);
  const float h = sqrt(2.0f) / 2.0f;
  Assert::AreEqual(v.x(), h, TH);
  Assert::AreEqual(v.y(), h, TH);
  Assert::AreEqual(v.z(), 0.0f, TH);
}

TEST_METHOD(test_StreamOutput)
{
  Quaternion q(5.0f, 2.0f, 4.5f, 8.9f);
  std::stringstream stream;
  stream << q;
  Assert::AreEqual(stream.str(), std::string("[5,2,4.5,8.9]"));
}

TEST_METHOD(test_StreamInput)
{
  /* Create stream with valid string */
  std::stringstream stream;
  stream << "[5.0,2.0,4.5,8.9]";

  /* Read the stream */
  Quaternion q;
  stream >> q;

  /* Validate results */
  Assert::AreEqual(q.getReal(), 5.0f);
  Assert::AreEqual(q.getI(), 2.0f);
  Assert::AreEqual(q.getJ(), 4.5f);
  Assert::AreEqual(q.getK(), 8.9f);
}
}
;
}
