/**
 * @file
 * @author Dan Nixon
 */

#include <CppUnitTest.h>

#include <Engine_Graphics/BoundingBox.h>
#include <Engine_Maths/Vector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Maths;

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
  TEST_METHOD(BoundingBox_InitEmpty)
  {
    BoundingBox<Vector3> b;
    Assert::Fail();
  }

  // TODO
};
#endif /* DOXYGEN_SKIP */
}
}
}
