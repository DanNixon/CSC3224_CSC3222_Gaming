/**
 * @file
 * @author Dan Nixon
 */

#include <CppUnitTest.h>

#include <Vector3.h>
#include <Vector2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
namespace Maths
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(Vector3Test)
{
public:
  TEST_METHOD(Vector3_InitEmpty)
  {
    Vector3 v;
    Assert::AreEqual(v.x(), 0.0f);
    Assert::AreEqual(v.y(), 0.0f);
    Assert::AreEqual(v.z(), 0.0f);
  }

  TEST_METHOD(Vector3_Init)
  {
    Vector3 v(3.5f, 8.9f, 4.7f);
    Assert::AreEqual(v.x(), 3.5f);
    Assert::AreEqual(v.y(), 8.9f);
    Assert::AreEqual(v.z(), 4.7f);
  }

  TEST_METHOD(Vector3_InitVector2)
  {
    Vector2 v2(3.5f, 8.9f);
    Vector3 v(v2);
    Assert::AreEqual(v.x(), 3.5f);
    Assert::AreEqual(v.y(), 8.9f);
  }

  TEST_METHOD(Vector3_toZero)
  {
    Vector3 v(3.5f, 8.9f, 4.7f);
    v.toZero();
    Assert::AreEqual(v.x(), 0.0f);
    Assert::AreEqual(v.y(), 0.0f);
    Assert::AreEqual(v.z(), 0.0f);
  }

  TEST_METHOD(Vector3_length2)
  {
    Vector3 v(5.0f, 5.0f, 5.0f);
    Assert::AreEqual(75.0f, v.length2());
  }

  TEST_METHOD(Vector3_length)
  {
    Vector3 v(5.0f, 5.0f, 5.0f);
    Assert::AreEqual(8.6603f, v.length(), 0.001f);
  }

  TEST_METHOD(Vector3_invert)
  {
    Vector3 v(5.0f, 3.0f, 2.0f);
    v.invert();
    Assert::AreEqual(-5.0f, v.x());
    Assert::AreEqual(-3.0f, v.y());
    Assert::AreEqual(-2.0f, v.z());
  }

  TEST_METHOD(Vector3_operatorMinusInverse)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2 = -v1;
    Assert::AreEqual(-5.0f, v2.x());
    Assert::AreEqual(-3.0f, v2.y());
    Assert::AreEqual(-2.0f, v2.z());
  }

  TEST_METHOD(Vector3_operatorPlus)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 1.0f, 0.5f);
    Vector3 v3 = v1 + v2;
    Assert::AreEqual(7.0f, v3.x());
    Assert::AreEqual(4.0f, v3.y());
    Assert::AreEqual(2.5f, v3.z());
  }

  TEST_METHOD(Vector3_operatorPlusEquals)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 1.0f, 0.5f);
    v1 += v2;
    Assert::AreEqual(7.0f, v1.x());
    Assert::AreEqual(4.0f, v1.y());
    Assert::AreEqual(2.5f, v1.z());
  }

  TEST_METHOD(Vector3_operatorMinus)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 1.0f, 0.5f);
    Vector3 v3 = v1 - v2;
    Assert::AreEqual(3.0f, v3.x());
    Assert::AreEqual(2.0f, v3.y());
    Assert::AreEqual(1.5f, v3.z());
  }

  TEST_METHOD(Vector3_operatorMinusEquals)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 1.0f, 0.5f);
    v1 -= v2;
    Assert::AreEqual(3.0f, v1.x());
    Assert::AreEqual(2.0f, v1.y());
    Assert::AreEqual(1.5f, v1.z());
  }

  TEST_METHOD(Vector3_operatorMultVec)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, 3.0f, 0.5f);
    Vector3 v3 = v1 * v2;
    Assert::AreEqual(10.0f, v3.x());
    Assert::AreEqual(9.0f, v3.y());
    Assert::AreEqual(1.0f, v3.z());
  }

  TEST_METHOD(Vector3_operatorMultFloat)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v3 = v1 * 2.0;
    Assert::AreEqual(10.0f, v3.x());
    Assert::AreEqual(6.0f, v3.y());
    Assert::AreEqual(4.0f, v3.z());
  }

  TEST_METHOD(Vector3_operatorDivVec)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(3.0f, 1.5f, 0.5f);
    Vector3 v3 = v1 / v2;
    Assert::AreEqual(1.6667f, v3.x(), 0.001f);
    Assert::AreEqual(2.0f, v3.y());
    Assert::AreEqual(4.0f, v3.z());
  }

  TEST_METHOD(Vector3_operatorDivFloat)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v3 = v1 / 2.0;
    Assert::AreEqual(2.5f, v3.x());
    Assert::AreEqual(1.5f, v3.y());
    Assert::AreEqual(1.0f, v3.z());
  }

  TEST_METHOD(Vector3_operatorEqual)
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

  TEST_METHOD(Vector3_operatorNotEqual)
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

  TEST_METHOD(Vector3_operatorIndexConst)
  {
    const Vector3 v1(5.0f, 3.0f, 2.0f);
    Assert::AreEqual(5.0f, v1[0]);
    Assert::AreEqual(3.0f, v1[1]);
    Assert::AreEqual(2.0f, v1[2]);
    Assert::AreEqual(0.0f, v1[3]);
  }

  TEST_METHOD(Vector3_operatorIndex)
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

  TEST_METHOD(Vector3_operatorStreamOutput)
  {
    Vector3 v(5.1f, 3.2f, 2.3f);
    std::stringstream stream;
    stream << v;
    Assert::AreEqual(std::string("[5.1,3.2,2.3]"), stream.str());
  }

  TEST_METHOD(Vector3_operatorStreamInput)
  {
    std::stringstream stream;
    stream << "[5.1,3.2,2.3]";

    Vector3 v;
    stream >> v;

    Assert::AreEqual(5.1f, v.x());
    Assert::AreEqual(3.2f, v.y());
    Assert::AreEqual(2.3f, v.z());
  }

  TEST_METHOD(Vector3_dot)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, -2.0f, 8.0f);
    float dotProd = Vector3::dot(v1, v2);
    Assert::AreEqual(20.0f, dotProd, 0.0001f);
  }

  TEST_METHOD(Vector3_cross)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(2.0f, -2.0f, 8.0f);
    Vector3 crossProd = Vector3::cross(v1, v2);
    Assert::AreEqual(28.0f, crossProd.x(), 0.0001f);
    Assert::AreEqual(-36.0f, crossProd.y(), 0.0001f);
    Assert::AreEqual(-16.0f, crossProd.z(), 0.0001f);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
