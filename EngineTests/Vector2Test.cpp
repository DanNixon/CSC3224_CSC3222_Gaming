#include "stdafx.h"
#include <CppUnitTest.h>

#include <Vector2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{		
	TEST_CLASS(Vector2Test)
	{
	public:
		
		TEST_METHOD(test_InitEmpty)
		{
      Vector2 v;
      Assert::AreEqual(v[0], 0.0f);
      Assert::AreEqual(v[1], 0.0f);
		}

    TEST_METHOD(test_Init)
    {
      Vector2 v(3.5f, 8.9f);
      Assert::AreEqual(v[0], 3.5f);
      Assert::AreEqual(v[1], 8.9f);
    }

	};
}