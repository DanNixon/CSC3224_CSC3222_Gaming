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
  TEST_METHOD(GraphLoader_LoadGraphFromFile)
  {
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;

    Assert::IsTrue(GraphLoader::LoadGraph(nodes, edges, "../resources/TODO.dat"));
  }
};
}
}
}