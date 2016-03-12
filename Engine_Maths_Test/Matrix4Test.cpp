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

  TEST_METHOD(Matrix4_RowCol)
  {
    Matrix4 m;
    m.setRow(0, Vector4(0.0f, 1.0f, 2.0f, 3.0f));
    m.setRow(1, Vector4(4.0f, 5.0f, 6.0f, 7.0f));
    m.setRow(2, Vector4(8.0f, 9.0f, 10.0f, 11.0f));
    m.setRow(3, Vector4(12.0f, 13.0f, 14.0f, 15.0f));

    Assert::AreEqual(0.0f, m.column(0)[0]);
    Assert::AreEqual(4.0f, m.column(0)[1]);
    Assert::AreEqual(8.0f, m.column(0)[2]);
    Assert::AreEqual(12.0f, m.column(0)[3]);

    Assert::AreEqual(1.0f, m.column(1)[0]);
    Assert::AreEqual(5.0f, m.column(1)[1]);
    Assert::AreEqual(9.0f, m.column(1)[2]);
    Assert::AreEqual(13.0f, m.column(1)[3]);

    Assert::AreEqual(2.0f, m.column(2)[0]);
    Assert::AreEqual(6.0f, m.column(2)[1]);
    Assert::AreEqual(10.0f, m.column(2)[2]);
    Assert::AreEqual(14.0f, m.column(2)[3]);

    Assert::AreEqual(3.0f, m.column(3)[0]);
    Assert::AreEqual(7.0f, m.column(3)[1]);
    Assert::AreEqual(11.0f, m.column(3)[2]);
    Assert::AreEqual(15.0f, m.column(3)[3]);
  }

  TEST_METHOD(Matrix4_ColRow)
  {
    Matrix4 m;
    m.setColumn(0, Vector4(0.0f, 4.0f, 8.0f, 12.0f));
    m.setColumn(1, Vector4(1.0f, 5.0f, 9.0f, 13.0f));
    m.setColumn(2, Vector4(2.0f, 6.0f, 10.0f, 14.0f));
    m.setColumn(3, Vector4(3.0f, 7.0f, 11.0f, 15.0f));

    Assert::AreEqual(0.0f, m.row(0)[0]);
    Assert::AreEqual(1.0f, m.row(0)[1]);
    Assert::AreEqual(2.0f, m.row(0)[2]);
    Assert::AreEqual(3.0f, m.row(0)[3]);

    Assert::AreEqual(4.0f, m.row(1)[0]);
    Assert::AreEqual(5.0f, m.row(1)[1]);
    Assert::AreEqual(6.0f, m.row(1)[2]);
    Assert::AreEqual(7.0f, m.row(1)[3]);

    Assert::AreEqual(8.0f, m.row(2)[0]);
    Assert::AreEqual(9.0f, m.row(2)[1]);
    Assert::AreEqual(10.0f, m.row(2)[2]);
    Assert::AreEqual(11.0f, m.row(2)[3]);

    Assert::AreEqual(12.0f, m.row(3)[0]);
    Assert::AreEqual(13.0f, m.row(3)[1]);
    Assert::AreEqual(14.0f, m.row(3)[2]);
    Assert::AreEqual(15.0f, m.row(3)[3]);
  }

  TEST_METHOD(Matrix4_LeftVector)
  {
    Matrix4 m;
    m.setRow(0, Vector4(0.0f, 1.0f, 2.0f, 3.0f));
    m.setRow(1, Vector4(4.0f, 5.0f, 6.0f, 7.0f));
    m.setRow(2, Vector4(8.0f, 9.0f, 10.0f, 11.0f));
    m.setRow(3, Vector4(12.0f, 13.0f, 14.0f, 15.0f));

    std::cout << m;

    Vector3 v = m.leftVector();

    Assert::AreEqual(0.0f, v.x());
    Assert::AreEqual(1.0f, v.y());
    Assert::AreEqual(2.0f, v.z());
  }

  TEST_METHOD(Matrix4_UpVector)
  {
    Matrix4 m;
    m.setRow(0, Vector4(0.0f, 1.0f, 2.0f, 3.0f));
    m.setRow(1, Vector4(4.0f, 5.0f, 6.0f, 7.0f));
    m.setRow(2, Vector4(8.0f, 9.0f, 10.0f, 11.0f));
    m.setRow(3, Vector4(12.0f, 13.0f, 14.0f, 15.0f));

    Vector3 v = m.upVector();

    Assert::AreEqual(4.0f, v.x());
    Assert::AreEqual(5.0f, v.y());
    Assert::AreEqual(6.0f, v.z());
  }

  TEST_METHOD(Matrix4_FacingVector)
  {
    Matrix4 m;
    m.setRow(0, Vector4(0.0f, 1.0f, 2.0f, 3.0f));
    m.setRow(1, Vector4(4.0f, 5.0f, 6.0f, 7.0f));
    m.setRow(2, Vector4(8.0f, 9.0f, 10.0f, 11.0f));
    m.setRow(3, Vector4(12.0f, 13.0f, 14.0f, 15.0f));

    Vector3 v = m.facingVector();

    Assert::AreEqual(8.0f, v.x());
    Assert::AreEqual(9.0f, v.y());
    Assert::AreEqual(10.0f, v.z());
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
