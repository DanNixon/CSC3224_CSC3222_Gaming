/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include <CppUnitTest.h>

#include <Engine_Maths/Vector2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Engine
{
namespace Maths
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(Vector2Test)
{
public:
  TEST_METHOD(Vector2_InitEmpty)
  {
    Vector2 v;
    Assert::AreEqual(v.x(), 0.0f);
    Assert::AreEqual(v.y(), 0.0f);
  }

  TEST_METHOD(Vector2_Init)
  {
    Vector2 v(3.5f, 8.9f);
    Assert::AreEqual(v.x(), 3.5f);
    Assert::AreEqual(v.y(), 8.9f);
  }

  TEST_METHOD(Vector2_toZero)
  {
    Vector2 v(3.5f, 8.9f);
    v.toZero();
    Assert::AreEqual(v.x(), 0.0f);
    Assert::AreEqual(v.y(), 0.0f);
  }

  TEST_METHOD(Vector2_length2)
  {
    Vector2 v(5.0f, 5.0f);
    Assert::AreEqual(50.0f, v.length2());
  }

  TEST_METHOD(Vector2_length)
  {
    Vector2 v(5.0f, 5.0f);
    Assert::AreEqual(7.0710f, v.length(), 0.001f);
  }

  TEST_METHOD(Vector2_invert)
  {
    Vector2 v(5.0f, 3.0f);
    v.invert();
    Assert::AreEqual(-5.0f, v.x());
    Assert::AreEqual(-3.0f, v.y());
  }

  TEST_METHOD(Vector2_operatorMinusInverse)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2 = -v1;
    Assert::AreEqual(-5.0f, v2.x());
    Assert::AreEqual(-3.0f, v2.y());
  }

  TEST_METHOD(Vector2_operatorPlus)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(2.0f, 1.0f);
    Vector2 v3 = v1 + v2;
    Assert::AreEqual(7.0f, v3.x());
    Assert::AreEqual(4.0f, v3.y());
  }

  TEST_METHOD(Vector2_operatorPlusEquals)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(2.0f, 1.0f);
    v1 += v2;
    Assert::AreEqual(7.0f, v1.x());
    Assert::AreEqual(4.0f, v1.y());
  }

  TEST_METHOD(Vector2_operatorMinus)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(2.0f, 1.0f);
    Vector2 v3 = v1 - v2;
    Assert::AreEqual(3.0f, v3.x());
    Assert::AreEqual(2.0f, v3.y());
  }

  TEST_METHOD(Vector2_operatorMinusEquals)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(2.0f, 1.0f);
    v1 -= v2;
    Assert::AreEqual(3.0f, v1.x());
    Assert::AreEqual(2.0f, v1.y());
  }

  TEST_METHOD(Vector2_operatorMultVec)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(2.0f, 3.0f);
    Vector2 v3 = v1 * v2;
    Assert::AreEqual(10.0f, v3.x());
    Assert::AreEqual(9.0f, v3.y());
  }

  TEST_METHOD(Vector2_operatorMultFloat)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v3 = v1 * 2.0;
    Assert::AreEqual(10.0f, v3.x());
    Assert::AreEqual(6.0f, v3.y());
  }

  TEST_METHOD(Vector2_operatorDivVec)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(3.0f, 1.5f);
    Vector2 v3 = v1 / v2;
    Assert::AreEqual(1.6667f, v3.x(), 0.001f);
    Assert::AreEqual(2.0f, v3.y());
  }

  TEST_METHOD(Vector2_operatorDivFloat)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v3 = v1 / 2.0;
    Assert::AreEqual(2.5f, v3.x());
    Assert::AreEqual(1.5f, v3.y());
  }

  TEST_METHOD(Vector2_operatorEqual)
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

  TEST_METHOD(Vector2_operatorNotEqual)
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

  TEST_METHOD(Vector2_operatorIndexConst)
  {
    const Vector2 v1(5.0f, 3.0f);
    Assert::AreEqual(5.0f, v1[0]);
    Assert::AreEqual(3.0f, v1[1]);
    Assert::AreEqual(0.0f, v1[2]);
  }

  TEST_METHOD(Vector2_operatorIndex)
  {
    Vector2 v1(5.0f, 3.0f);
    Assert::AreEqual(5.0f, v1[0]);
    Assert::AreEqual(3.0f, v1[1]);
    v1[0] = 12.0f;
    v1[1] = 8.0f;
    Assert::AreEqual(12.0f, v1[0]);
    Assert::AreEqual(8.0f, v1[1]);
  }

  TEST_METHOD(Vector2_operatorStreamOutput)
  {
    Vector2 v(5.1f, 3.2f);
    std::stringstream stream;
    stream << v;
    Assert::AreEqual(std::string("[5.1,3.2]"), stream.str());
  }

  TEST_METHOD(Vector2_operatorStreamInput)
  {
    std::stringstream stream;
    stream << "[5.1,3.2]";

    Vector2 v;
    stream >> v;

    Assert::AreEqual(5.1f, v.x());
    Assert::AreEqual(3.2f, v.y());
  }

  TEST_METHOD(Vector2_dot)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(2.0f, -2.0f);
    float dotProd = Vector2::dot(v1, v2);
    Assert::AreEqual(4.0f, dotProd, 0.0001f);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
