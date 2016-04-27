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
    Assert::AreEqual(11.18f, e.staticCost(), 0.01f);
    Assert::AreEqual(11.18f, e.cost(), 0.01f);

    e.setWeight(0.1f);

    // With weight = 0.1
    Assert::AreEqual(0.1f, e.weight());
    Assert::AreEqual(11.18f, e.staticCost(), 0.01f);
    Assert::AreEqual(1.118f, e.cost(), 0.01f);

    e.setWeight(5.0f);

    // With weight = 5
    Assert::AreEqual(5.0f, e.weight());
    Assert::AreEqual(11.18f, e.staticCost(), 0.01f);
    Assert::AreEqual(55.90f, e.cost(), 0.01f);
  }

  TEST_METHOD(Edge_Equality)
  {
    Node n1("n1");
    Node n2("n2");
    Node n3("n3");

    Edge e1(&n1, &n2);
    Edge e2(&n1, &n2);
    Edge e3(&n2, &n1);
    Edge e4(&n1, &n3);

    Assert::IsTrue(e1 == e2);
    Assert::IsTrue(e1 == e3);
    Assert::IsTrue(e2 == e3);
    Assert::IsFalse(e1 != e2);
    Assert::IsFalse(e1 != e3);
    Assert::IsFalse(e2 != e3);

    Assert::IsFalse(e1 == e4);
    Assert::IsTrue(e1 != e4);
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
