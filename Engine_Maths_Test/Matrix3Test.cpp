/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include <CppUnitTest.h>

#include <Engine_Maths/Matrix3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Engine
{
namespace Maths
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(Matrix3Test)
{
public:
  TEST_METHOD(Matrix3_InitEmpty)
  {
    Matrix3 m;
  }

  TEST_METHOD(Matrix3_RowCol)
  {
    Matrix3 m;
    m.setRow(0, Vector3(0.0f, 1.0f, 2.0f));
    m.setRow(1, Vector3(4.0f, 5.0f, 6.0f));
    m.setRow(2, Vector3(8.0f, 9.0f, 10.0f));
    m.setRow(3, Vector3(12.0f, 13.0f, 14.0f));

    Assert::AreEqual(0.0f, m.column(0)[0]);
    Assert::AreEqual(4.0f, m.column(0)[1]);
    Assert::AreEqual(8.0f, m.column(0)[2]);

    Assert::AreEqual(1.0f, m.column(1)[0]);
    Assert::AreEqual(5.0f, m.column(1)[1]);
    Assert::AreEqual(9.0f, m.column(1)[2]);

    Assert::AreEqual(2.0f, m.column(2)[0]);
    Assert::AreEqual(6.0f, m.column(2)[1]);
    Assert::AreEqual(10.0f, m.column(2)[2]);
  }

  TEST_METHOD(Matrix3_ColRow)
  {
    Matrix3 m;
    m.setColumn(0, Vector3(0.0f, 4.0f, 8.0f));
    m.setColumn(1, Vector3(1.0f, 5.0f, 9.0f));
    m.setColumn(2, Vector3(2.0f, 6.0f, 10.0f));

    Assert::AreEqual(0.0f, m.row(0)[0]);
    Assert::AreEqual(1.0f, m.row(0)[1]);
    Assert::AreEqual(2.0f, m.row(0)[2]);

    Assert::AreEqual(4.0f, m.row(1)[0]);
    Assert::AreEqual(5.0f, m.row(1)[1]);
    Assert::AreEqual(6.0f, m.row(1)[2]);

    Assert::AreEqual(8.0f, m.row(2)[0]);
    Assert::AreEqual(9.0f, m.row(2)[1]);
    Assert::AreEqual(10.0f, m.row(2)[2]);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
