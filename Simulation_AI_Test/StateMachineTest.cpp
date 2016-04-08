#include "CppUnitTest.h"

#include "MockState.h"
#include "MockStateMachine.h"

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
  TEST_METHOD(StateMachine_update)
  {
    MockStateMachine m;
    m.value = 0;

    IState * s1 = new MockState("state1", m.rootState(), &m, 5, "state2/state2.1");
    IState * s11 = new MockState("state1.1", s1, &m, 4, "state1/state1.2");
    IState * s12 = new MockState("state1.2", s1, &m, 3, "state1/state1.2/state1.2.1");
    IState * s121 = new MockState("state1.2.1", s12, &m, 2, "state2/state2.1");
    IState * s2 = new MockState("state2", m.rootState(), &m, 6, "state1/state1.1");
    IState * s21 = new MockState("state2.1", s2, &m, 1, "state2");

    // Default activated state (1)
    s1->setActivation(true);
    Assert::IsFalse(m.transfer());
    Assert::AreEqual(std::string("state1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 1
    m.operate();
    Assert::IsTrue(IStatePtrList{ s1 } == m.m_operatedStack);

    // Transfer from 1 to 2.1
    m.value = 5;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state2/state2.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 2.1
    m.operate();
    Assert::IsTrue(IStatePtrList{ s2, s21 } == m.m_operatedStack);

    // Transfer from 2.1 to 2
    m.value = 1;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state2"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 2
    m.operate();
    Assert::IsTrue(IStatePtrList{ s2 } == m.m_operatedStack);

    // No transfer from 2 
    m.value = 0;
    Assert::IsFalse(m.transfer());
    Assert::AreEqual(std::string("state2"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 2
    m.operate();
    Assert::IsTrue(IStatePtrList{ s2 } == m.m_operatedStack);

    // Transfer from 2 to 1.1
    m.value = 6;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state1/state1.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 1.1
    m.operate();
    Assert::IsTrue(IStatePtrList{ s1, s11 } == m.m_operatedStack);

    // Transfer from 1.1 to 1.2
    m.value = 4;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state1/state1.2"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 1.2
    m.operate();
    Assert::IsTrue(IStatePtrList{ s1, s12 } == m.m_operatedStack);

    // No transfer from 1.2
    m.value = 0;
    Assert::IsFalse(m.transfer());
    Assert::AreEqual(std::string("state1/state1.2"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 1.2
    m.operate();
    Assert::IsTrue(IStatePtrList{ s1, s12 } == m.m_operatedStack);

    // Transfer from 1.2 to 1.2.1
    m.value = 3;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state1/state1.2/state1.2.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 1.2.1
    m.operate();
    Assert::IsTrue(IStatePtrList{ s1, s12, s121 } == m.m_operatedStack);

    // No transfer from 1.2.1
    m.value = 0;
    Assert::IsFalse(m.transfer());
    Assert::AreEqual(std::string("state1/state1.2/state1.2.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 1.2.1
    m.operate();
    Assert::IsTrue(IStatePtrList{ s1, s12, s121 } == m.m_operatedStack);

    // Transfer from 1.2.1 (1) to 2.1
    m.value = 5;
    Assert::IsTrue(m.transfer());
    Assert::AreEqual(std::string("state2/state2.1"), StateMachine::BranchToString(m.activeStateBranch()));

    // Operate on 2.1
    m.operate();
    Assert::IsTrue(IStatePtrList{ s2, s21 } == m.m_operatedStack);
  }

  TEST_METHOD(StateMachine_activation_activeStateBranch)
  {
    StateMachine m;

    IState * s1 = new IState("state1", m.rootState(), &m);
    IState * s11 = new IState("state1.1", s1, &m);
    IState * s12 = new IState("state1.2", s1, &m);
    IState * s121 = new IState("state1.2.1", s12, &m);
    IState * s2 = new IState("state2", m.rootState(), &m);
    IState * s21 = new IState("state2.1", s2, &m);

    // Test activation
    s12->setActivation(true);
    Assert::IsTrue(s1 == m.rootState()->activeChild());
    Assert::IsTrue(s12 == s1->activeChild());
    Assert::IsNull(s12->activeChild());

    // Test active branch
    s121->setActivation(true);
    std::vector<IState *> branch = m.activeStateBranch();
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
    IState * s1 = new IState("state1", nullptr, nullptr);
    IState * s12 = new IState("state1.2", s1, nullptr);
    IState * s121 = new IState("state1.2.1", s12, nullptr);

    std::vector<IState *> branch = { s1, s12, s121 };
    std::string branchStr = StateMachine::BranchToString(branch);

    Assert::AreEqual(std::string("state1/state1.2/state1.2.1"), branchStr);
  }
};
}
}
}