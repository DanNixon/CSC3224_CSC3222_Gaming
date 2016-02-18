/** @file */

#include "stdafx.h"
#include <CppUnitTest.h>

#include <Vector2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{
TEST_CLASS(Vector2Test){public : TEST_METHOD(test_InitEmpty){Vector2 v;
Assert::AreEqual(v.x(), 0.0f);
Assert::AreEqual(v.y(), 0.0f);
}

TEST_METHOD(test_Init)
{
  Vector2 v(3.5f, 8.9f);
  Assert::AreEqual(v.x(), 3.5f);
  Assert::AreEqual(v.y(), 8.9f);
}

TEST_METHOD(test_toZero)
{
  Vector2 v(3.5f, 8.9f);
  v.toZero();
  Assert::AreEqual(v.x(), 0.0f);
  Assert::AreEqual(v.y(), 0.0f);
}

TEST_METHOD(test_length2)
{
  Vector2 v(5.0f, 5.0f);
  Assert::AreEqual(50.0f, v.length2());
}

TEST_METHOD(test_length)
{
  Vector2 v(5.0f, 5.0f);
  Assert::AreEqual(7.0710f, v.length(), 0.001f);
}

TEST_METHOD(test_normalise)
{
  Vector2 v(5.0f, 3.0f);
  v.normalise();
  Assert::AreEqual(0.857f, v.x(), 0.001f);
  Assert::AreEqual(0.515f, v.y(), 0.001f);
  Assert::AreEqual(1.0f, v.length(), 0.001f);
}

TEST_METHOD(test_invert)
{
  Vector2 v(5.0f, 3.0f);
  v.invert();
  Assert::AreEqual(-5.0f, v.x());
  Assert::AreEqual(-3.0f, v.y());
}

TEST_METHOD(test_operatorMinusInverse)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2 = -v1;
  Assert::AreEqual(-5.0f, v2.x());
  Assert::AreEqual(-3.0f, v2.y());
}

TEST_METHOD(test_operatorPlus)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(2.0f, 1.0f);
  Vector2 v3 = v1 + v2;
  Assert::AreEqual(7.0f, v3.x());
  Assert::AreEqual(4.0f, v3.y());
}

TEST_METHOD(test_operatorPlusEquals)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(2.0f, 1.0f);
  v1 += v2;
  Assert::AreEqual(7.0f, v1.x());
  Assert::AreEqual(4.0f, v1.y());
}

TEST_METHOD(test_operatorMinus)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(2.0f, 1.0f);
  Vector2 v3 = v1 - v2;
  Assert::AreEqual(3.0f, v3.x());
  Assert::AreEqual(2.0f, v3.y());
}

TEST_METHOD(test_operatorMinusEquals)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(2.0f, 1.0f);
  v1 -= v2;
  Assert::AreEqual(3.0f, v1.x());
  Assert::AreEqual(2.0f, v1.y());
}

TEST_METHOD(test_operatorMultVec)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(2.0f, 3.0f);
  Vector2 v3 = v1 * v2;
  Assert::AreEqual(10.0f, v3.x());
  Assert::AreEqual(9.0f, v3.y());
}

TEST_METHOD(test_operatorMultFloat)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v3 = v1 * 2.0;
  Assert::AreEqual(10.0f, v3.x());
  Assert::AreEqual(6.0f, v3.y());
}

TEST_METHOD(test_operatorDivVec)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(3.0f, 1.5f);
  Vector2 v3 = v1 / v2;
  Assert::AreEqual(1.6667f, v3.x(), 0.001f);
  Assert::AreEqual(2.0f, v3.y());
}

TEST_METHOD(test_operatorDivFloat)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v3 = v1 / 2.0;
  Assert::AreEqual(2.5f, v3.x());
  Assert::AreEqual(1.5f, v3.y());
}

TEST_METHOD(test_operatorEqual)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(5.0f, 3.0f);
  Vector2 v3(5.1f, 3.1f);

  Assert::IsTrue(v1 == v1);
  Assert::IsTrue(v2 == v2);
  Assert::IsTrue(v3 == v3);

  Assert::IsTrue(v1 == v2);
  Assert::IsFalse(v2 == v3);
  Assert::IsFalse(v1 == v3);
}

TEST_METHOD(test_operatorNotEqual)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(5.0f, 3.0f);
  Vector2 v3(5.1f, 3.1f);

  Assert::IsFalse(v1 != v1);
  Assert::IsFalse(v2 != v2);
  Assert::IsFalse(v3 != v3);

  Assert::IsFalse(v1 != v2);
  Assert::IsTrue(v2 != v3);
  Assert::IsTrue(v1 != v3);
}

TEST_METHOD(test_operatorIndexConst)
{
  const Vector2 v1(5.0f, 3.0f);
  Assert::AreEqual(5.0f, v1[0]);
  Assert::AreEqual(3.0f, v1[1]);
  Assert::AreEqual(0.0f, v1[2]);
}

TEST_METHOD(test_operatorIndex)
{
  Vector2 v1(5.0f, 3.0f);
  Assert::AreEqual(5.0f, v1[0]);
  Assert::AreEqual(3.0f, v1[1]);
  v1[0] = 12.0f;
  v1[1] = 8.0f;
  Assert::AreEqual(12.0f, v1[0]);
  Assert::AreEqual(8.0f, v1[1]);
}

TEST_METHOD(test_operatorStreamOutput)
{
  Vector2 v(5.1f, 3.2f);
  std::stringstream stream;
  stream << v;
  Assert::AreEqual(std::string("[5.1,3.2]"), stream.str());
}

TEST_METHOD(test_operatorStreamInput)
{
  std::stringstream stream;
  stream << "[5.1,3.2]";

  Vector2 v;
  stream >> v;

  Assert::AreEqual(5.1f, v.x());
  Assert::AreEqual(3.2f, v.y());
}

TEST_METHOD(test_distance)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(6.0f, 4.0f);
  float dist = Vector2::distance(v1, v2);
  Assert::AreEqual(1.4142f, dist, 0.001f);
}

TEST_METHOD(test_distance2)
{
  Vector2 v1(5.0f, 3.0f);
  Vector2 v2(6.0f, 4.0f);
  float dist2 = Vector2::distance2(v1, v2);
  Assert::AreEqual(2.0f, dist2, 0.001f);
}
}
;
}
