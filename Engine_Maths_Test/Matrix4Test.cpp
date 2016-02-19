/**
 * @file
 * @author Dan Nixon
 */

#include "stdafx.h"
#include <CppUnitTest.h>

#include <Matrix4.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(Matrix4Test)
{
public:
  TEST_METHOD(test_InitEmpty)
  {
    Matrix4 m;
  }
};
#endif /* DOXYGEN_SKIP */
}
