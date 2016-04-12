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
  TEST_METHOD(Node_Test)
  {
    Assert::Fail();
  }

  TEST_METHOD(Node_StreamOutput)
  {
    Node n();
    std::stringstream stream;
    stream << n;
    Assert::AreEqual(std::string("[5,2,4.5,8.9]"), stream.str());
  }
};
}
}
}