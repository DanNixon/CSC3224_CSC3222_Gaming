/**
 * @file
 * @author Dan Nixon
 */

#include "CppUnitTest.h"

#include <INIKeyValueStore.h>
#include <KVNode.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
namespace IO
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(INIKeyValueStoreTest)
{
public:
  TEST_METHOD(test_LoadINIFromStream)
  {
    // Sample INI file
    std::stringstream stream;
    stream << "aaa=yes" << std::endl
           << "" << std::endl
           << "bbb=yes,no" << std::endl
           << "[group one]" << std::endl
           << "ccc=true" << std::endl
           << "a b c=maybe" << std::endl;

    // Parse
    INIKeyValueStore store;
    Assert::IsTrue(store.load(stream));

    KVNode & root = store.root();

    // Test root node name and size
    Assert::AreEqual(std::string(), root.name());
    Assert::AreEqual((size_t) 2, root.numKeys());
    Assert::AreEqual((size_t) 1, root.numChildren());

    // Test root node values
    Assert::IsTrue(root.hasKey("aaa"));
    Assert::AreEqual(std::string("yes"), root.get("aaa"));
    Assert::IsFalse(root.hasKey("zzz"));

    // Test root node children
    Assert::IsTrue(root.hasChild("group one"));

    KVNode child1 = root.child("group one");

    // Test child node name and size
    Assert::AreEqual(std::string("group one"), child1.name());
    Assert::AreEqual((size_t) 2, child1.numKeys());
    Assert::AreEqual((size_t) 0, child1.numChildren());

    // Test child node values
    Assert::IsTrue(child1.hasKey("ccc"));
    Assert::AreEqual(std::string("true"), child1.get("ccc"));
    Assert::IsTrue(child1.hasKey("a b c"));
    Assert::AreEqual(std::string("maybe"), child1.get("a b c"));
  }

  TEST_METHOD(test_BuildINIFromStream)
  {
    // Build test structure
    INIKeyValueStore store;

    KVNode & root = store.root();
    root.set("hello", "1234567");
    root.set("test45", "99");

    KVNode child1("options area_1");
    child1.set("big world", "true");
    child1.set("really_big_world", "false");
    root.addChild(child1);

    KVNode child2("options area_2");
    child2.set("detail", "good");
    child2.set("speed", "good enough");
    root.addChild(child2);

    // Output
    std::stringstream stream;
    Assert::IsTrue(store.save(stream));

    // Expected
    const std::string expected =
      "hello=1234567\n"
      "test45=99\n"
      "[options area_1]\n"
      "big world=true\n"
      "really_big_world=false\n"
      "[options area_2]\n"
      "detail=good\n"
      "speed=good enough\n";

    // Test
    Assert::AreEqual(expected, stream.str());
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
