/** @file */

#include "stdafx.h"
#include <CppUnitTest.h>

#include <stdexcept>
#include <functional>

#include <Vector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{
TEST_CLASS(Vector3Test)
{
public:
  TEST_METHOD(test_InitEmpty)
  {
    Vector3 v;
    Assert::AreEqual(v.x(), 0.0f);
    Assert::AreEqual(v.y(), 0.0f);
    Assert::AreEqual(v.z(), 0.0f);
  }

  TEST_METHOD(test_Init)
  {
    Vector3 v(3.5f, 8.9f, 4.7f);
    Assert::AreEqual(v.x(), 3.5f);
    Assert::AreEqual(v.y(), 8.9f);
    Assert::AreEqual(v.z(), 4.7f);
  }

  TEST_METHOD(test_toZero)
  {
    Vector3 v(3.5f, 8.9f, 4.7f);
    v.toZero();
    Assert::AreEqual(v.x(), 0.0f);
    Assert::AreEqual(v.y(), 0.0f);
    Assert::AreEqual(v.z(), 0.0f);
  }

  TEST_METHOD(test_length2)
  {
    Vector3 v(5.0f, 5.0f, 5.0f);
    Assert::AreEqual(75.0f, v.length2());
  }

  TEST_METHOD(test_length)
  {
    Vector3 v(5.0f, 5.0f, 5.0f);
    Assert::AreEqual(8.6603f, v.length(), 0.001f);
  }

  TEST_METHOD(test_normalise)
  {
    Vector3 v(5.0f, 3.0f, 2.0f);
    v.normalise();
    Assert::AreEqual(0.811f, v.x(), 0.001f);
    Assert::AreEqual(0.486f, v.y(), 0.001f);
    Assert::AreEqual(0.324f, v.z(), 0.001f);
  }

  TEST_METHOD(test_invert)
  {
    Vector3 v(5.0f, 3.0f, 2.0f);
    v.invert();
    Assert::AreEqual(-5.0f, v.x());
    Assert::AreEqual(-3.0f, v.y());
    Assert::AreEqual(-2.0f, v.z());
  }

  TEST_METHOD(test_inverse)
  {
    Vector3 v(5.0f, 3.0f, 2.0f);
    Vector3 v2 = v.inverse();
    Assert::AreEqual(-5.0f, v2.x());
    Assert::AreEqual(-3.0f, v2.y());
    Assert::AreEqual(-2.0f, v2.z());
  }

  TEST_METHOD(test_operatorPlus)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 1.0f, 0.5f);
    Vector3 v3 = v1 + v2;
    Assert::AreEqual(7.0f, v3.x());
    Assert::AreEqual(4.0f, v3.y());
    Assert::AreEqual(2.5f, v3.z());
  }

  TEST_METHOD(test_operatorPlusEquals)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 1.0f, 0.5f);
    v1 += v2;
    Assert::AreEqual(7.0f, v1.x());
    Assert::AreEqual(4.0f, v1.y());
    Assert::AreEqual(2.5f, v1.z());
  }

  TEST_METHOD(test_operatorMinus)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 1.0f, 0.5f);
    Vector3 v3 = v1 - v2;
    Assert::AreEqual(3.0f, v3.x());
    Assert::AreEqual(2.0f, v3.y());
    Assert::AreEqual(1.5f, v3.z());
  }

  TEST_METHOD(test_operatorMinusEquals)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 1.0f, 0.5f);
    v1 -= v2;
    Assert::AreEqual(3.0f, v1.x());
    Assert::AreEqual(2.0f, v1.y());
    Assert::AreEqual(1.5f, v1.z());
  }

  TEST_METHOD(test_operatorMinusInverse)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2 = -v1;
    Assert::AreEqual(-5.0f, v2.x());
    Assert::AreEqual(-3.0f, v2.y());
    Assert::AreEqual(-2.0f, v2.z());
  }

  TEST_METHOD(test_operatorMultVec)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 3.0f, 0.5f);
    Vector3 v3 = v1 * v2;
    Assert::AreEqual(10.0f, v3.x());
    Assert::AreEqual(9.0f, v3.y());
    Assert::AreEqual(1.0f, v3.z());
  }

  TEST_METHOD(test_operatorMultFloat)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v3 = v1 * 2.0;
    Assert::AreEqual(10.0f, v3.x());
    Assert::AreEqual(6.0f, v3.y());
    Assert::AreEqual(4.0f, v3.z());
  }

  TEST_METHOD(test_operatorDivVec)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(3.0f, 1.5f, 0.5f);
    Vector3 v3 = v1 / v2;
    Assert::AreEqual(1.6667f, v3.x(), 0.001f);
    Assert::AreEqual(2.0f, v3.y());
    Assert::AreEqual(4.0f, v3.z());
  }

  TEST_METHOD(test_operatorDivFloat)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v3 = v1 / 2.0;
    Assert::AreEqual(2.5f, v3.x());
    Assert::AreEqual(1.5f, v3.y());
    Assert::AreEqual(1.0f, v3.z());
  }

  TEST_METHOD(test_operatorEqual)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(5.0f, 3.0f, 2.0f);
    Vector3 v3(5.1f, 3.1f, 2.1f);

    Assert::IsTrue(v1 == v1);
    Assert::IsTrue(v2 == v2);
    Assert::IsTrue(v3 == v3);

    Assert::IsTrue(v1 == v2);
    Assert::IsFalse(v2 == v3);
    Assert::IsFalse(v1 == v3);
  }

  TEST_METHOD(test_operatorNotEqual)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(5.0f, 3.0f, 2.0f);
    Vector3 v3(5.1f, 3.1f, 2.1f);

    Assert::IsFalse(v1 != v1);
    Assert::IsFalse(v2 != v2);
    Assert::IsFalse(v3 != v3);

    Assert::IsFalse(v1 != v2);
    Assert::IsTrue(v2 != v3);
    Assert::IsTrue(v1 != v3);
  }

  TEST_METHOD(test_operatorIndexConst)
  {
    const Vector3 v1(5.0f, 3.0f, 2.0f);
    Assert::AreEqual(5.0f, v1[0]);
    Assert::AreEqual(3.0f, v1[1]);
    Assert::AreEqual(2.0f, v1[2]);
    Assert::AreEqual(0.0f, v1[3]);
  }

  TEST_METHOD(test_operatorIndex)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Assert::AreEqual(5.0f, v1[0]);
    Assert::AreEqual(3.0f, v1[1]);
    Assert::AreEqual(2.0f, v1[2]);
    v1[0] = 12.0f;
    v1[1] = 8.0f;
    v1[2] = 16.0f;
    Assert::AreEqual(12.0f, v1[0]);
    Assert::AreEqual(8.0f, v1[1]);
    Assert::AreEqual(16.0f, v1[2]);
  }

  TEST_METHOD(test_operatorStreamOutput)
  {
    Vector3 v(5.1f, 3.2f, 2.3f);
    std::stringstream stream;
    stream << v;
    Assert::AreEqual(std::string("Vector3[5.1,3.2,2.3]"), stream.str());
  }
};
}
