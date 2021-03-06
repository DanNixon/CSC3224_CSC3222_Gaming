/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "CppUnitTest.h"

#include "Engine_Maths/Vector2.h"
#include "Engine_Maths/Vector3.h"
#include "Engine_Maths/Vector4.h"
#include "Engine_Maths/VectorOperations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Engine
{
namespace Maths
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(VectorOperationsTest)
{
public:
  TEST_METHOD(VectorOperations_Vector2_normalise)
  {
    Vector2 v(5.0f, 3.0f);
    VectorOperations::Normalise(v);
    Assert::AreEqual(0.857f, v.x(), 0.001f);
    Assert::AreEqual(0.515f, v.y(), 0.001f);
    Assert::AreEqual(1.0f, v.length(), 0.001f);
  }

  TEST_METHOD(VectorOperations_Vector3_normalise)
  {
    Vector3 v(5.0f, 3.0f, 2.0f);
    VectorOperations::Normalise(v);
    Assert::AreEqual(0.811f, v.x(), 0.001f);
    Assert::AreEqual(0.486f, v.y(), 0.001f);
    Assert::AreEqual(0.324f, v.z(), 0.001f);
    Assert::AreEqual(1.0f, v.length(), 0.001f);
  }

  TEST_METHOD(VectorOperations_Vector4_normalise)
  {
    Vector4 v(5.0f, 3.0f, 2.0f, 8.0f);
    VectorOperations::Normalise(v);
    Assert::AreEqual(0.495f, v.x(), 0.001f);
    Assert::AreEqual(0.297f, v.y(), 0.001f);
    Assert::AreEqual(0.198f, v.z(), 0.001f);
    Assert::AreEqual(0.792f, v.w(), 0.001f);
    Assert::AreEqual(1.0f, v.length(), 0.001f);
  }

  TEST_METHOD(VectorOperations_Vector2_distance)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(6.0f, 4.0f);
    float dist = VectorOperations::Distance(v1, v2);
    Assert::AreEqual(1.4142f, dist, 0.001f);
  }

  TEST_METHOD(VectorOperations_Vector3_distance)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(6.0f, 4.0f, 9.0f);
    float dist = VectorOperations::Distance(v1, v2);
    Assert::AreEqual(7.1414f, dist, 0.001f);
  }

  TEST_METHOD(VectorOperations_Vector4_distance)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(6.0f, 4.0f, 9.0f, 4.0f);
    float dist = VectorOperations::Distance(v1, v2);
    Assert::AreEqual(8.1853f, dist, 0.001f);
  }

  TEST_METHOD(VectorOperations_Vector2_distance2)
  {
    Vector2 v1(5.0f, 3.0f);
    Vector2 v2(6.0f, 4.0f);
    float dist2 = VectorOperations::Distance2(v1, v2);
    Assert::AreEqual(2.0f, dist2, 0.001f);
  }

  TEST_METHOD(VectorOperations_Vector3_distance2)
  {
    Vector3 v1(5.0f, 3.0f, 2.0f);
    Vector3 v2(6.0f, 4.0f, 9.0f);
    float dist2 = VectorOperations::Distance2(v1, v2);
    Assert::AreEqual(51.0f, dist2, 0.001f);
  }

  TEST_METHOD(VectorOperations_Vector4_distance2)
  {
    Vector4 v1(5.0f, 3.0f, 2.0f, 8.0f);
    Vector4 v2(6.0f, 4.0f, 9.0f, 4.0f);
    float dist2 = VectorOperations::Distance2(v1, v2);
    Assert::AreEqual(67.0f, dist2, 0.001f);
  }

  TEST_METHOD(VectorOperatons_Vector2_Projection)
  {
    Vector2 a(2.0f, 1.0f);
    Vector2 b(-3.0f, 4.0f);
    Vector2 p = VectorOperations::Project(a, b);
    Assert::AreEqual(0.24f, p.x(), 0.001f);
    Assert::AreEqual(-0.32f, p.y(), 0.001f);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
