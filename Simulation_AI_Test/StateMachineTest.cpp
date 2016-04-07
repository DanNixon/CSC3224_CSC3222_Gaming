#include "CppUnitTest.h"

#include "FakeState.h"
#include "FakeStateMachine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Simulation
{
namespace AI
{
namespace Test
{
TEST_CLASS(StateMachineTest)
{
public:
  TEST_METHOD(StateMachine_FullTest)
  {
    MockStateMachine sm;
    sm.value = 0;
  }

  TEST_METHOD(StateMachine_activeChild)
  {
    StateMachine m;

    State * s1 = new MockState("state1", m.rootState(), 0, "");
    State * s11 = new MockState("state1.1", s1, 0, "");
    State * s12 = new MockState("state1.2", s1, 0, "");
    State * s121 = new MockState("state1.2.1", s12, 0, "");
    State * s2 = new MockState("state2", m.rootState(), 0, "");
    State * s21 = new MockState("state2.1", s2, 0, "");

    s12->setActivation(true);

    Assert::IsTrue(s1 == m.rootState()->activeChild());
    Assert::IsTrue(s12 == s1->activeChild());
    Assert::IsNull(s12->activeChild());

    s12->setActivation(false);
    Assert::IsNull(m.rootState()->activeChild());
    Assert::IsNull(s1->activeChild());
    Assert::IsNull(s12->activeChild());
  }
};
}
}
}