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

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[3], nodes[3]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)1, path.size());
    Assert::IsTrue(nodes[3] == path[0]);
  }

  TEST_METHOD(AStarTest_TestPath_1_fwd)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[3], nodes[5]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)3, path.size());
    Assert::IsTrue(nodes[3] == path[0]);
    Assert::IsTrue(nodes[4] == path[1]);
    Assert::IsTrue(nodes[5] == path[2]);
  }
  
  TEST_METHOD(AStarTest_TestPath_1_rev)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[5], nodes[3]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)3, path.size());
    Assert::IsTrue(nodes[5] == path[0]);
    Assert::IsTrue(nodes[4] == path[1]);
    Assert::IsTrue(nodes[3] == path[2]);
  }

  TEST_METHOD(AStarTest_TestPath_2_fwd)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[6], nodes[1]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)3, path.size());
    Assert::IsTrue(nodes[6] == path[0]);
    Assert::IsTrue(nodes[3] == path[1]);
    Assert::IsTrue(nodes[1] == path[2]);
  }
  
  TEST_METHOD(AStarTest_TestPath_2_rev)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[1], nodes[6]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)3, path.size());
    Assert::IsTrue(nodes[1] == path[0]);
    Assert::IsTrue(nodes[3] == path[1]);
    Assert::IsTrue(nodes[6] == path[2]);
  }

  TEST_METHOD(AStarTest_TestPath_3_fwd)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[8], nodes[0]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)3, path.size());
    Assert::IsTrue(nodes[8] == path[0]);
    Assert::IsTrue(nodes[4] == path[1]);
    Assert::IsTrue(nodes[0] == path[2]);
  }
  
  TEST_METHOD(AStarTest_TestPath_3_rev)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[0], nodes[8]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)3, path.size());
    Assert::IsTrue(nodes[0] == path[0]);
    Assert::IsTrue(nodes[4] == path[1]);
    Assert::IsTrue(nodes[8] == path[2]);
  }

  TEST_METHOD(AStarTest_TestPath_4_fwd)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[7], nodes[4]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)2, path.size());
    Assert::IsTrue(nodes[7] == path[0]);
    Assert::IsTrue(nodes[4] == path[1]);
  }
  
  TEST_METHOD(AStarTest_TestPath_4_rev)
  {
    // Load test graph
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    GraphLoader::LoadGraph(nodes, edges, "../../../../resources/test_graph.dat");

    // Run path finding
    AStar pathFinder(nodes);
    Assert::IsTrue(pathFinder.findPath(nodes[4], nodes[7]));

    // Assert path
    std::vector<Node *> &path = pathFinder.path();
    Assert::AreEqual((size_t)2, path.size());
    Assert::IsTrue(nodes[4] == path[0]);
    Assert::IsTrue(nodes[7] == path[1]);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
