/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "CppUnitTest.h"

#include <Engine_IO/INIKeyValueStore.h>
#include <Engine_IO/KVNode.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
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
  TEST_METHOD(INIKeyValueStore_LoadINIFromStream)
  {
    // Sample INI string
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

    KVNode & root = store.rootKVNode();

    // Test root node name and size
    Assert::AreEqual(std::string(), root.name());
    Assert::AreEqual((size_t) 2, root.numKeys());
    Assert::AreEqual((size_t) 1, root.numChildren());

    // Test root node values
    Assert::IsTrue(root.hasKey("aaa"));
    Assert::AreEqual(std::string("yes"), root.keys()["aaa"]);
    Assert::IsFalse(root.hasKey("zzz"));

    // Test root node children
    Assert::IsTrue(root.hasChild("group one"));

    KVNode child1 = root.children()["group one"];

    // Test child node name and size
    Assert::AreEqual(std::string("group one"), child1.name());
    Assert::AreEqual((size_t) 2, child1.numKeys());
    Assert::AreEqual((size_t) 0, child1.numChildren());

    // Test child node values
    Assert::IsTrue(child1.hasKey("ccc"));
    Assert::AreEqual(std::string("true"), child1.keys()["ccc"]);
    Assert::IsTrue(child1.hasKey("a b c"));
    Assert::AreEqual(std::string("maybe"), child1.keys()["a b c"]);
  }

  TEST_METHOD(INIKeyValueStore_BuildINIFromStream)
  {
    // Build test structure
    INIKeyValueStore store;

    KVNode & root = store.rootKVNode();
    root.keys()["hello"] = "1234567";
    root.keys()["test45"] = "99";

    KVNode child1("options area_1");
    child1.keys()["big world"] = "true";
    child1.keys()["really_big_world"] = "false";
    root.addChild(child1);

    KVNode child2("options area_2");
    child2.keys()["detail"] = "good";
    child2.keys()["speed"] = "good enough";
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
