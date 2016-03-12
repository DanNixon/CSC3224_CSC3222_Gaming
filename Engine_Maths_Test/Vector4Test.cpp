/**
 * @file
 * @author Dan Nixon
 */

#include <CppUnitTest.h>

#include <Vector4.h>
#include <Vector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
namespace Maths
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(Vector4Test)
{
public:
  TEST_METHOD(Vector4_InitEmpty)
  {
    Vector4 v;
    Assert::AreEqual(v.x(), 0.0f);
    Assert::AreEqual(v.y(), 0.0f);
    Assert::AreEqual(v.z(), 0.0f);
    Assert::AreEqual(v.w(), 1.0f);
  }
  
  TEST_METHOD(Vector4_Init)
  {
    Vector4 v(3.5f, 8.9f, 4.7f, 1.5f);
    Assert::AreEqual(v.x(), 3.5f);
    Assert::AreEqual(v.y(), 8.9f);
    Assert::AreEqual(v.z(), 4.7f);
    Assert::AreEqual(v.w(), 1.5f);
  }

  TEST_METHOD(Vector4_InitVector3)
  {
    Vector3 v3(3.5f, 8.9f, 4.7f);
    Vector4 v(v3);
    Assert::AreEqual(v.x(), 3.5f);
    Assert::AreEqual(v.y(), 8.9f);
    Assert::AreEqual(v.z(), 4.7f);
    Assert::AreEqual(v.w(), 1.0f);
  }

  TEST_METHOD(Vector4_toZero)
  {
    Vector4 v(3.5f, 8.9f, 4.7f, 1.5f);
    v.toZero();
    Assert::AreEqual(v.x(), 0.0f);
    Assert::AreEqual(v.y(), 0.0f);
    Assert::AreEqual(v.z(), 0.0f);
    Assert::AreEqual(v.w(), 0.0f);
  }

  TEST_METHOD(Vector4_length2)
  {
    Vector4 v(5.0f, 5.0f, 5.0f, 5.0f);
    Assert::AreEqual(100.0f, v.length2());
  }

  TEST_METHOD(Vector4_length)
  {
    Vector4 v(5.0f, 5.0f, 5.0f, 5.0f);
    Assert::AreEqual(10.0f, v.length(), 0.001f);
  }

  TEST_METHOD(Vector4_invert)
  {
    Vector4 v(5.0f, 3.0f, 2.0f, 8.0f);
    v.invert();
    Assert::AreEqual(-5.0f, v.x());
    Assert::AreEqual(-3.0f, v.y());
    Assert::AreEqual(-2.0f, v.z());
    Assert::AreEqual(-8.0f, v.w());
  }

  TEST_METHOD(Vector4_operatorMinusInverse)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2 = -v1;
    Assert::AreEqual(-5.0f, v2.x());
    Assert::AreEqual(-3.0f, v2.y());
    Assert::AreEqual(-2.0f, v2.z());
    Assert::AreEqual(-8.0f, v2.w());
  }

  TEST_METHOD(Vector4_operatorPlus)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(2.0f, 1.0f, 0.5f, 4.0f);
    Vector4 v3 = v1 + v2;
    Assert::AreEqual(7.0f, v3.x());
    Assert::AreEqual(4.0f, v3.y());
    Assert::AreEqual(2.5f, v3.z());
    Assert::AreEqual(12.0f, v3.w());
  }

  TEST_METHOD(Vector4_operatorPlusEquals)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(2.0f, 1.0f, 0.5f, 4.0f);
    v1 += v2;
    Assert::AreEqual(7.0f, v1.x());
    Assert::AreEqual(4.0f, v1.y());
    Assert::AreEqual(2.5f, v1.z());
    Assert::AreEqual(12.0f, v1.w());
  }

  TEST_METHOD(Vector4_operatorMinus)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(2.0f, 1.0f, 0.5f, 4.0f);
    Vector4 v3 = v1 - v2;
    Assert::AreEqual(3.0f, v3.x());
    Assert::AreEqual(2.0f, v3.y());
    Assert::AreEqual(1.5f, v3.z());
    Assert::AreEqual(4.0f, v3.w());
  }

  TEST_METHOD(Vector4_operatorMinusEquals)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(2.0f, 1.0f, 0.5f, 4.0f);
    v1 -= v2;
    Assert::AreEqual(3.0f, v1.x());
    Assert::AreEqual(2.0f, v1.y());
    Assert::AreEqual(1.5f, v1.z());
    Assert::AreEqual(4.0f, v1.w());
  }

  TEST_METHOD(Vector4_operatorMultVec)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(2.0f, 3.0f, 0.5f, 4.0f);
    Vector4 v3 = v1 * v2;
    Assert::AreEqual(10.0f, v3.x());
    Assert::AreEqual(9.0f, v3.y());
    Assert::AreEqual(1.0f, v3.z());
    Assert::AreEqual(32.0f, v3.w());
  }

  TEST_METHOD(Vector4_operatorMultFloat)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v3 = v1 * 2.0;
    Assert::AreEqual(10.0f, v3.x());
    Assert::AreEqual(6.0f, v3.y());
    Assert::AreEqual(4.0f, v3.z());
    Assert::AreEqual(16.0f, v3.w());
  }

  TEST_METHOD(Vector4_operatorDivVec)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(3.0f, 1.5f, 0.5f, 2.0f);
    Vector4 v3 = v1 / v2;
    Assert::AreEqual(1.6667f, v3.x(), 0.001f);
    Assert::AreEqual(2.0f, v3.y());
    Assert::AreEqual(4.0f, v3.z());
    Assert::AreEqual(4.0f, v3.w());
  }

  TEST_METHOD(Vector4_operatorDivFloat)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v3 = v1 / 2.0;
    Assert::AreEqual(2.5f, v3.x());
    Assert::AreEqual(1.5f, v3.y());
    Assert::AreEqual(1.0f, v3.z());
    Assert::AreEqual(4.0f, v3.w());
  }

  TEST_METHOD(Vector4_operatorEqual)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v3(5.1f, 3.1f, 2.1f, 8.1f);

    Assert::IsTrue(v1 == v1);
    Assert::IsTrue(v2 == v2);
    Assert::IsTrue(v3 == v3);

    Assert::IsTrue(v1 == v2);
    Assert::IsFalse(v2 == v3);
    Assert::IsFalse(v1 == v3);
  }

  TEST_METHOD(Vector4_operatorNotEqual)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v3(5.1f, 3.1f, 2.1f, 8.1f);

    Assert::IsFalse(v1 != v1);
    Assert::IsFalse(v2 != v2);
    Assert::IsFalse(v3 != v3);

    Assert::IsFalse(v1 != v2);
    Assert::IsTrue(v2 != v3);
    Assert::IsTrue(v1 != v3);
  }

  TEST_METHOD(Vector4_operatorIndexConst)
  {
    const Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Assert::AreEqual(5.0f, v1[0]);
    Assert::AreEqual(3.0f, v1[1]);
    Assert::AreEqual(2.0f, v1[2]);
    Assert::AreEqual(8.0f, v1[3]);
    Assert::AreEqual(0.0f, v1[4]);
  }

  TEST_METHOD(Vector4_operatorIndex)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Assert::AreEqual(5.0f, v1[0]);
    Assert::AreEqual(3.0f, v1[1]);
    Assert::AreEqual(2.0f, v1[2]);
    Assert::AreEqual(8.0f, v1[3]);
    v1[0] = 12.0f;
    v1[1] = 8.0f;
    v1[2] = 16.0f;
    v1[3] = 32.0f;
    Assert::AreEqual(12.0f, v1[0]);
    Assert::AreEqual(8.0f, v1[1]);
    Assert::AreEqual(16.0f, v1[2]);
    Assert::AreEqual(32.0f, v1[3]);
  }

  TEST_METHOD(Vector4_operatorStreamOutput)
  {
    Vector4 v(5.1f, 3.2f, 2.3f, 8.4f);
    std::stringstream stream;
    stream << v;
    Assert::AreEqual(std::string("[5.1,3.2,2.3,8.4]"), stream.str());
  }

  TEST_METHOD(Vector4_operatorStreamInput)
  {
    std::stringstream stream;
    stream << "[5.1,3.2,2.3,8.4]";

    Vector4 v;
    stream >> v;

    Assert::AreEqual(5.1f, v.x());
    Assert::AreEqual(3.2f, v.y());
    Assert::AreEqual(2.3f, v.z());
    Assert::AreEqual(8.4f, v.w());
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
