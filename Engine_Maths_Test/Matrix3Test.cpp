/** @file */

#include "stdafx.h"
#include <CppUnitTest.h>

#include <Matrix3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{
  TEST_CLASS(Matrix3Test)
  {
  public:
    TEST_METHOD(test_InitEmpty)
    {
      Matrix3 m;
    }
  };
}
