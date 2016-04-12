/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "CppUnitTest.h"

#include <Simulation_PathFinding/GraphLoader.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Simulation
{
namespace PathFinding
{
namespace Test
{
TEST_CLASS(GraphLoaderTest)
{
public:
  TEST_METHOD(GraphLoader_FailNoFile)
  {
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;

    Assert::IsFalse(GraphLoader::LoadGraph(nodes, edges, "../resources/notafile.dat"));
    Assert::AreEqual((size_t)0, nodes.size());
    Assert::AreEqual((size_t)0, edges.size());
  }

  TEST_METHOD(GraphLoader_LoadGraphFromFile)
  {
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;

    Assert::IsTrue(GraphLoader::LoadGraph(nodes, edges, "../resources/buckminsterfullerene.dat"));
    Assert::AreEqual((size_t)1, nodes.size()); //TODO
    Assert::AreEqual((size_t)2, edges.size()); //TODO

    //TODO: test some nodes/edges
  }
};
}
}
}