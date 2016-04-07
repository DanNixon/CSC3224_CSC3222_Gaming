#include "CppUnitTest.h"

#include <Simulation_AI/StateContainer.h>

#include "FakeState.h"

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

    container.addChild(new MockState("state1", nullptr, 0, ""));
    Assert::IsTrue(container.hasChildren());
  }

  TEST_METHOD(StateContainer_activation)
  {
    StateContainer container;
    State * s1 = new MockState("state1", nullptr, 0, "");
    State * s11 =   new MockState("state1.1", s1, 0, "");
    State * s12 =   new MockState("state1.2", s1, 0, "");
    State * s121 =  new MockState("state1.2.1", s12, 0, "");
    State * s2 = new MockState("state2", nullptr, 0, "");
    State * s21 =   new MockState("state2.1", s2, 0, "");
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
    State * s1 = new MockState("state1", nullptr, 0, "");
    State * s11 = new MockState("state1.1", s1, 0, "");
    State * s12 = new MockState("state1.2", s1, 0, "");
    State * s121 = new MockState("state1.2.1", s12, 0, "");
    State * s2 = new MockState("state2", nullptr, 0, "");
    State * s21 = new MockState("state2.1", s2, 0, "");
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