#include "CppUnitTest.h"

#include <Simulation_AI/State.h>
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
TEST_CLASS(StateContainerTest)
{
public:
  TEST_METHOD(StateContainer_hasChildren)
  {
    StateContainer container;
    Assert::IsFalse(container.hasChildren());

    container.addChild(new State("state1", nullptr, nullptr));
    Assert::IsTrue(container.hasChildren());
  }

  TEST_METHOD(StateContainer_activation)
  {
    StateContainer container;
    State * s1 = new State("state1", nullptr, nullptr);
    State * s11 = new State("state1.1", s1, nullptr);
    State * s12 = new State("state1.2", s1, nullptr);
    State * s121 = new State("state1.2.1", s12, nullptr);
    State * s2 = new State("state2", nullptr, nullptr);
    State * s21 = new State("state2.1", s2, nullptr);
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
    State * s1 = new State("state1", nullptr, nullptr);
    State * s11 = new State("state1.1", s1, nullptr);
    State * s12 = new State("state1.2", s1, nullptr);
    State * s121 = new State("state1.2.1", s12, nullptr);
    State * s2 = new State("state2", nullptr, nullptr);
    State * s21 = new State("state2.1", s2, nullptr);
    container.addChild(s1);
    container.addChild(s2);

    std::vector<State *> branch = container.findState("state1/state1.2/state1.2.1");

    Assert::AreEqual((size_t) 3, branch.size());
    Assert::IsTrue(s1 == branch[0]);
    Assert::IsTrue(s12 == branch[1]);
    Assert::IsTrue(s121 == branch[2]);
  }
};
}
}
}