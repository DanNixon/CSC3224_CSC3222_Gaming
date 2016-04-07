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
  TEST_METHOD(StateMachine_transfer)
  {
    MockStateMachine m;
    m.value = 0;

    State * s1 = new MockState("state1", m.rootState(), 5, "state2/state2.1");
    State * s11 = new MockState("state1.1", s1, 4, "state1/state1.2");
    State * s12 = new MockState("state1.2", s1, 3, "state1/state1.2/state1.2.1");
    State * s121 = new MockState("state1.2.1", s12, 2, "state2/state2.1");
    State * s2 = new MockState("state2", m.rootState(), 6, "state1/state1.1");
    State * s21 = new MockState("state2.1", s2, 1, "state2");

    // Default activated state
    s1->setActivation(true);
    Assert::IsFalse(m.transfer());
    Assert::AreEqual(std::string("state1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Transfer from 1 to 2.1
    m.value = 5;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state2/state2.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Transfer from 2.1 to 2
    m.value = 1;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state2"), StateMachine::BranchToString(m.activeStateBranch()));

    // No transfer from 2 
    m.value = 0;
    Assert::IsFalse(m.transfer());
    Assert::AreEqual(std::string("state2"), StateMachine::BranchToString(m.activeStateBranch()));

    // Transfer from 2 to 1.1
    m.value = 6;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state1/state1.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Transfer from 1.1 to 1.2
    m.value = 4;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state1/state1.2"), StateMachine::BranchToString(m.activeStateBranch()));

    // No transfer from 1.2
    m.value = 0;
    Assert::IsFalse(m.transfer());
    Assert::AreEqual(std::string("state1/state1.2"), StateMachine::BranchToString(m.activeStateBranch()));

    // Transfer from 1.2 to 1.2.1
    m.value = 3;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state1/state1.2/state1.2.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // No transfer from 1.2.1
    m.value = 0;
    Assert::IsFalse(m.transfer());
    Assert::AreEqual(std::string("state1/state1.2/state1.2.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Transfer from 1.2.1 (1) to 2.1
    m.value = 5;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state2/state2.1"), StateMachine::BranchToString(m.activeStateBranch()));
  }

  TEST_METHOD(StateMachine_activation_activeStateBranch)
  {
    StateMachine m;

    State * s1 = new MockState("state1", m.rootState(), 0, "");
    State * s11 = new MockState("state1.1", s1, 0, "");
    State * s12 = new MockState("state1.2", s1, 0, "");
    State * s121 = new MockState("state1.2.1", s12, 0, "");
    State * s2 = new MockState("state2", m.rootState(), 0, "");
    State * s21 = new MockState("state2.1", s2, 0, "");

    // Test activation
    s12->setActivation(true);
    Assert::IsTrue(s1 == m.rootState()->activeChild());
    Assert::IsTrue(s12 == s1->activeChild());
    Assert::IsNull(s12->activeChild());

    // Test active branch
    s121->setActivation(true);
    std::vector<State *> branch = m.activeStateBranch();
    Assert::AreEqual((size_t) 3, branch.size());
    Assert::IsTrue(s1 == branch[0]);
    Assert::IsTrue(s12 == branch[1]);
    Assert::IsTrue(s121 == branch[2]);

    // Test deactivation
    s121->setActivation(false);
    Assert::IsNull(m.rootState()->activeChild());
    Assert::IsNull(s1->activeChild());
    Assert::IsNull(s12->activeChild());
  }

  TEST_METHOD(StateMachine_BranchToString)
  {
    State * s1 = new MockState("state1", nullptr, 0, "");
    State * s12 = new MockState("state1.2", s1, 0, "");
    State * s121 = new MockState("state1.2.1", s12, 0, "");

    std::vector<State *> branch = { s1, s12, s121 };
    std::string branchStr = StateMachine::BranchToString(branch);

    Assert::AreEqual(std::string("state1/state1.2/state1.2.1"), branchStr);
  }
};
}
}
}