/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "CppUnitTest.h"

#include <Simulation_PathFinding/Edge.h>
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
TEST_CLASS(EdgeTest)
{
public:
  TEST_METHOD(Edge_DefaultName)
  {
    Node n1("n1");
    Node n2("n2");
    Edge e(&n1, &n2);
    Assert::AreEqual(std::string("n1-n2"), e.id());
  }

  TEST_METHOD(Edge_Test_Create)
  {
    Node n1("n1");
    Node n2("n2");
    Edge e(&n1, &n2, "e1");
    Assert::AreEqual(std::string("e1"), e.id());
    Assert::IsTrue(&n1 == e.nodeA());
    Assert::IsTrue(&n2 == e.nodeB());
  }

  TEST_METHOD(Edge_Test_CostWeight)
  {
    Node n1("n1", Vector3(10.0f, 0.0f, 0.0f));
    Node n2("n2", Vector3(0.0f, 5.0f, 0.0f));
    Edge e(&n1, &n2, "e1");

    // With default weight = 1
    Assert::AreEqual(1.0f, e.weight());
    Assert::AreEqual(125.0f, e.staticCost());
    Assert::AreEqual(125.0f, e.cost());

    e.setWeight(0.1f);

    // With weight = 0.1
    Assert::AreEqual(0.1f, e.weight());
    Assert::AreEqual(125.0f, e.staticCost());
    Assert::AreEqual(12.5f, e.cost());

    e.setWeight(5.0f);

    // With weight = 5
    Assert::AreEqual(5.0f, e.weight());
    Assert::AreEqual(125.0f, e.staticCost());
    Assert::AreEqual(625.0f, e.cost());
  }

  TEST_METHOD(Edge_StreamOutput)
  {
    Node n1("n1");
    Node n2("n2");
    Edge e(&n1, &n2, "ed");
    std::stringstream stream;
    stream << e;
    Assert::AreEqual(std::string("ed:n1,n2"), stream.str());
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
