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
TEST_CLASS(Matrix4Test)
{
public:
  TEST_METHOD(test_InitEmpty)
  {
    Matrix4 m;
  }
};
}
