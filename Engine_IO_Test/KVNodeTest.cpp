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
TEST_CLASS(KVNodeTest)
{
public:
  TEST_METHOD(KVNode_UpdateFromOther)
  {
    // Tree A
    KVNode treeA;
    treeA.keys()["a"] = "1";
    treeA.keys()["c"] = "7";

    KVNode treeAchild1("child1");
    treeAchild1.keys()["d"] = "11";
    treeA.addChild(treeAchild1);

    // Tree B
    KVNode treeB;
    treeB.keys()["a"] = "1";
    treeB.keys()["b"] = "2";
    treeB.keys()["c"] = "3";

    KVNode treeBchild1("child1");
    treeBchild1.keys()["d"] = "11";
    treeBchild1.keys()["e"] = "15";
    treeBchild1.keys()["f"] = "19";
    treeB.addChild(treeBchild1);

    KVNode treeBchild2("child2");
    treeBchild2.keys()["x"] = "0";
    treeBchild2.keys()["y"] = "1";
    treeBchild2.keys()["z"] = "2";
    treeB.addChild(treeBchild2);

    // Test
    treeA.updateFromOther(treeB);

    // Assert keys
    Assert::AreEqual(std::string("1"), treeA.keys()["a"]);
    Assert::AreEqual(std::string("2"), treeA.keys()["b"]);
    Assert::AreEqual(std::string("7"), treeA.keys()["c"]);

    // Assert child 1
    Assert::AreEqual(std::string("11"), treeA.children()["child1"].keys()["d"]);
    Assert::AreEqual(std::string("15"), treeA.children()["child1"].keys()["e"]);
    Assert::AreEqual(std::string("19"), treeA.children()["child1"].keys()["f"]);

    // Assert child 2
    Assert::IsTrue(treeA.hasChild("child2"));
    Assert::AreEqual(std::string("0"), treeA.children()["child2"].keys()["x"]);
    Assert::AreEqual(std::string("1"), treeA.children()["child2"].keys()["y"]);
    Assert::AreEqual(std::string("2"), treeA.children()["child2"].keys()["z"]);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
