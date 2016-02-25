/**
 * @file
 * @author Dan Nixon
 */

#include <CppUnitTest.h>

#include <Matrix4.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
namespace Maths
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(Matrix4Test)
{
public:
  TEST_METHOD(Matrix4_InitEmpty)
  {
    Matrix4 m;
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
