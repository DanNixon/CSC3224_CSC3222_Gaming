/**
 * @file
 * @author Dan Nixon
 */

#include "stdafx.h"
#include <CppUnitTest.h>

#include <Matrix3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(Matrix3Test)
{
public:
  TEST_METHOD(test_InitEmpty)
  {
    Matrix3 m;
  }
};
#endif /* DOXYGEN_SKIP */
}
