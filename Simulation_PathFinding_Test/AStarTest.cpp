/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "CppUnitTest.h"

#include <Simulation_PathFinding/AStar.h>
#include <Simulation_PathFinding/Edge.h>
#include <Simulation_PathFinding/GraphLoader.h>
#include <Simulation_PathFinding/Node.h>

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Maths;

// clang-format off
namespace Simulation
{
namespace PathFinding
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(AStarTest)
{
public:
  TEST_METHOD(AStarTest_LoadTestGraph)
  {
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;

    // Test load
    Assert::IsTrue(GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat"));

    // Assert node/edge count
    Assert::AreEqual((size_t)9, nodes.size());
    Assert::AreEqual((size_t)20, edges.size());
  }

  TEST_METHOD(AStarTest_StartAndEndNodeIdentical)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    AStar pathFinder(nodes);

    Assert::IsTrue(pathFinder.findPath(nodes[3], nodes[3]));

    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)1, path.size());
    Assert::IsTrue(nodes[3] == path[0]);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
