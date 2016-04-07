#include "CppUnitTest.h"

#include <Engine_Utility/StringUtils.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Engine
{
namespace Utility
{
namespace Test
{
TEST_CLASS(StringUtilsTest)
{
public:
  TEST_METHOD(StringUtils_Trim)
  {
    std::string a = StringUtils::Trim("   hello");
    Assert::AreEqual(std::string("hello"), a);

    std::string b = StringUtils::Trim("hello  ");
    Assert::AreEqual(std::string("hello"), b);

    std::string c = StringUtils::Trim("   hello  ");
    Assert::AreEqual(std::string("hello"), c);

    std::string d = StringUtils::Trim("hello");
    Assert::AreEqual(std::string("hello"), d);

    std::string e = StringUtils::Trim("   ");
    Assert::AreEqual(std::string(""), e);

    std::string f = StringUtils::Trim("");
    Assert::AreEqual(std::string(""), f);
  }

  TEST_METHOD(StringUtils_Split)
  {
    std::vector<std::string> a = StringUtils::Split("one,two,three,,four,", ',');
    Assert::AreEqual((size_t) 4, a.size());
    Assert::AreEqual(std::string("one"), a[0]);
    Assert::AreEqual(std::string("two"), a[1]);
    Assert::AreEqual(std::string("three"), a[2]);
    Assert::AreEqual(std::string("four"), a[3]);
  }

  TEST_METHOD(StringUtils_SanitizeFilename)
  {
    std::string s = StringUtils::SanitizeFilename("Snooker Loopy!");
    Assert::AreEqual(std::string("SnookerLoopy"), s);
  }

  TEST_METHOD(StringUtils_DirectoryFromPath)
  {
    std::string s = StringUtils::DirectoryFromPath("c:\\stuff\\thing.txt");
    Assert::AreEqual(std::string("c:\\stuff"), s);
  }

  TEST_METHOD(StringUtils_FilenameFromPath)
  {
    std::string s = StringUtils::FilenameFromPath("c:\\stuff\\thing.txt");
    Assert::AreEqual(std::string("thing.txt"), s);
  }

  TEST_METHOD(StringUtils_BasenameFromFilename)
  {
    std::string s = StringUtils::BasenameFromFilename("thing.txt");
    Assert::AreEqual(std::string("thing"), s);
  }

  TEST_METHOD(StringUtils_ExtFromFilename)
  {
    std::string s = StringUtils::ExtFromFilename("thing.txt");
    Assert::AreEqual(std::string("txt"), s);
  }
};
}
}
}