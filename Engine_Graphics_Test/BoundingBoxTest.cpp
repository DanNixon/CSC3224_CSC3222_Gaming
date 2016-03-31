/**
 * @file
 * @author Dan Nixon
 */

#include <CppUnitTest.h>

#include <Engine_Graphics/BoundingBox.h>
#include <Engine_Maths/Vector2.h>
#include <Engine_Maths/Vector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Maths;

// clang-format off
namespace Engine
{
namespace Graphics
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(BoundingBoxTest)
{
public:
  TEST_METHOD(BoundingBox_Init)
  {
    BoundingBox<Vector3> b(Vector3(-1.0f, -2.0f, -3.0f), Vector3(1.0f, 2.0f, 3.0f));

    Assert::AreEqual(-1.0f, b.lowerLeft().x());
    Assert::AreEqual(-2.0f, b.lowerLeft().y());
    Assert::AreEqual(-3.0f, b.lowerLeft().z());
    Assert::AreEqual(1.0f, b.upperRight().x());
    Assert::AreEqual(2.0f, b.upperRight().y());
    Assert::AreEqual(3.0f, b.upperRight().z());
  }

  TEST_METHOD(BoundingBox_Size)
  {
    BoundingBox<Vector3> b(Vector3(-1.0f, -2.0f, -3.0f), Vector3(1.0f, 2.0f, 3.0f));
    Vector3 d = b.size();

    Assert::AreEqual(2.0f, d.x());
    Assert::AreEqual(4.0f, d.y());
    Assert::AreEqual(6.0f, d.z());
  }

  TEST_METHOD(BoundingBox_PointInside)
  {
    BoundingBox<Vector3> b(Vector3(-1.0f, -2.0f, -3.0f), Vector3(1.0f, 2.0f, 3.0f));

    Assert::IsTrue(b.pointInside(Vector3(0.0f, 0.0f, 0.0f)));

    // Points on boundary are inside
    Assert::IsTrue(b.pointInside(Vector3(-1.0f, 0.0f, 0.0f)));
    Assert::IsTrue(b.pointInside(Vector3(0.0f, -2.0f, 0.0f)));
    Assert::IsTrue(b.pointInside(Vector3(0.0f, 0.0f, -3.0f)));

    Assert::IsTrue(b.pointInside(Vector3(1.0f, 0.0f, 0.0f)));
    Assert::IsTrue(b.pointInside(Vector3(0.0f, 2.0f, 0.0f)));
    Assert::IsTrue(b.pointInside(Vector3(0.0f, 0.0f, 3.0f)));

    // Points outside of boundary
    Assert::IsFalse(b.pointInside(Vector3(-1.1f, 0.0f, 0.0f)));
    Assert::IsFalse(b.pointInside(Vector3(0.0f, -2.1f, 0.0f)));
    Assert::IsFalse(b.pointInside(Vector3(0.0f, 0.0f, -3.1f)));

    Assert::IsFalse(b.pointInside(Vector3(1.1f, 0.0f, 0.0f)));
    Assert::IsFalse(b.pointInside(Vector3(0.0f, 2.1f, 0.0f)));
    Assert::IsFalse(b.pointInside(Vector3(0.0f, 0.0f, 3.1f)));
  }

  TEST_METHOD(BoundingBox_ResizeByPoint)
  {
    BoundingBox<Vector2> b;

    b.resizeByPoint(Vector2(-0.5f, -1.0f));
    b.resizeByPoint(Vector2(1.0f, 0.5f));
    Assert::IsTrue(Vector2(-0.5f, -1.0f) == b.lowerLeft());
    Assert::IsTrue(Vector2(1.0f, 0.5f) == b.upperRight());

    b.resizeByPoint(Vector2(50.0f, 0.0f));
    Assert::IsTrue(Vector2(-0.5f, -1.0f) == b.lowerLeft());
    Assert::IsTrue(Vector2(50.0f, 0.5f) == b.upperRight());
    
    b.resizeByPoint(Vector2(0.2f, -10.0f));
    Assert::IsTrue(Vector2(-0.5f, -10.0f) == b.lowerLeft());
    Assert::IsTrue(Vector2(50.0f, 0.5f) == b.upperRight());
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
