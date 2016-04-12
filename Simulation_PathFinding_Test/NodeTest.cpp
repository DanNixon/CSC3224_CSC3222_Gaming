/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 2.
 */

#include "CppUnitTest.h"

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
TEST_CLASS(NodeTest)
{
public:
  TEST_METHOD(Node_Test_Default)
  {
    Node n("n1");
    Assert::AreEqual(std::string("n1"), n.id());
    Assert::AreEqual(0.0f, n.position()[0]);
    Assert::AreEqual(0.0f, n.position()[1]);
    Assert::AreEqual(0.0f, n.position()[2]);
  }

  TEST_METHOD(Node_Test)
  {
    Node n("n1", Vector3(1.0f, 2.0f, 3.0f));
    Assert::AreEqual(std::string("n1"), n.id());
    Assert::AreEqual(1.0f, n.position()[0]);
    Assert::AreEqual(2.0f, n.position()[1]);
    Assert::AreEqual(3.0f, n.position()[2]);
  }

  TEST_METHOD(Node_StreamOutput)
  {
    Node n("n1", Vector3(1.0f, 2.0f, 3.0f));
    std::stringstream stream;
    stream << n;
    Assert::AreEqual(std::string("Node(id=n1, position=[1,2,3])"), stream.str());
  }
};
}
}
}