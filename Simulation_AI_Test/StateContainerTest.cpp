/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#include "CppUnitTest.h"

#include <Simulation_AI/IState.h>
#include <Simulation_AI/StateContainer.h>

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Simulation
{
namespace AI
{
namespace Test
{
#ifndef DOXYGEN_SKIP
TEST_CLASS(StateContainerTest)
{
public:
  TEST_METHOD(StateContainer_hasChildren)
  {
    StateContainer container;
    Assert::IsFalse(container.hasChildren());

    container.addChild(new IState("state1", nullptr, nullptr));
    Assert::IsTrue(container.hasChildren());
  }

  TEST_METHOD(StateContainer_activation)
  {
    StateContainer container;
    IState * s1 = new IState("state1", nullptr, nullptr);
    IState * s11 = new IState("state1.1", s1, nullptr);
    IState * s12 = new IState("state1.2", s1, nullptr);
    IState * s121 = new IState("state1.2.1", s12, nullptr);
    IState * s2 = new IState("state2", nullptr, nullptr);
    IState * s21 = new IState("state2.1", s2, nullptr);
    container.addChild(s1);
    container.addChild(s2);

    // Test activation
    s12->setActivation(true);
    Assert::IsTrue(s12 == s1->activeChild());
    Assert::IsNull(s12->activeChild());

    // Test deactivation
    s12->setActivation(false);
    Assert::IsNull(container.activeChild());
    Assert::IsNull(s1->activeChild());
    Assert::IsNull(s12->activeChild());
  }

  TEST_METHOD(StateContainer_findState)
  {
    StateContainer container;
    IState * s1 = new IState("state1", nullptr, nullptr);
    IState * s11 = new IState("state1.1", s1, nullptr);
    IState * s12 = new IState("state1.2", s1, nullptr);
    IState * s121 = new IState("state1.2.1", s12, nullptr);
    IState * s2 = new IState("state2", nullptr, nullptr);
    IState * s21 = new IState("state2.1", s2, nullptr);
    container.addChild(s1);
    container.addChild(s2);

    std::vector<IState *> branch = container.findState("state1/state1.2/state1.2.1");

    Assert::AreEqual((size_t) 3, branch.size());
    Assert::IsTrue(s1 == branch[0]);
    Assert::IsTrue(s12 == branch[1]);
    Assert::IsTrue(s121 == branch[2]);
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
