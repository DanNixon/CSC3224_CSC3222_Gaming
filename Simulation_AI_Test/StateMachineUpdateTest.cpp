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
TEST_CLASS(StateMachineUpdateTest)
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
    m.entryStack.clear();
    m.exitStack.clear();

    testTransfer(m, 0, "state1");

    // Operate on 1
    testOperate(m, { s1 });

    // Transfer from 1 to 2.1
    testTransfer(m, 5, "state2/state2.1", { s1 }, { s2, s21 });

    // Operate on 2.1
    testOperate(m, { s2, s21 });

    // Transfer from 2.1 to 2
    testTransfer(m, 1, "state2", { s21 }, { });
    
    // Operate on 2
    testOperate(m, { s2 });

    // No transfer from 2
    testTransfer(m, 0, "state2");

    // Operate on 2
    testOperate(m, { s2 });

    // Transfer from 2 to 1.1
    testTransfer(m, 6, "state1/state1.1", { s2 }, { s1, s11 });
    
    // Operate on 1.1
    testOperate(m, { s1, s11 });

    // Transfer from 1.1 to 1.2
    testTransfer(m, 4, "state1/state1.2", { s11 }, { s12 });
    
    // Operate on 1.2
    testOperate(m, { s1, s12 });

    // No transfer from 1.2
    testTransfer(m, 0, "state1/state1.2");
    
    // Operate on 1.2
    testOperate(m, { s1, s12 });

    // Transfer from 1.2 to 1.2.1
    testTransfer(m, 3, "state1/state1.2/state1.2.1", { }, { s121 });
    
    // Operate on 1.2.1
    testOperate(m, { s1, s12, s121 });

    // No transfer from 1.2.1
    testTransfer(m, 0, "state1/state1.2/state1.2.1");
    
    // Operate on 1.2.1
    testOperate(m, { s1, s12, s121 });

    // Transfer from 1.2.1 (1) to 2.1
    testTransfer(m, 5, "state2/state2.1", { s121, s12, s1 }, { s2, s21 });

    // Operate on 2.1
    testOperate(m, { s2, s21 });
  }

  /**
   * @brief Performs transfer test.
   * @param m Reference to the state machine under test
   */
  void testTransfer(MockStateMachine &m, int transferValue, const std::string &expectedBranch,
                    const IStatePtrList &expectedExitStack = {}, const IStatePtrList &expectedEntryStack = {})
  {
    m.value = transferValue;

    // Transfer value of zero should not give any transfer
    if (transferValue == 0)
      Assert::IsFalse(m.transfer());
    else
      Assert::IsTrue(m.transfer());

    // Validate current state branch
    Assert::AreEqual(expectedBranch, StateMachine::BranchToString(m.activeStateBranch()));

    // Validate state entry and exit stacks
    if (transferValue == 0)
    {
      Assert::AreEqual((size_t)0, m.entryStack.size());
      Assert::AreEqual((size_t)0, m.exitStack.size());
    }
    else
    {
      Assert::IsTrue(expectedExitStack == m.exitStack);
      Assert::IsTrue(expectedEntryStack == m.entryStack);
    }

    // Reset state entry and exit stacks
    m.entryStack.clear();
    m.exitStack.clear();
  }

  /**
   * @brief Performs operation test.
   * @param m Reference to the state machine under test
   * @param expectedStack Vector containing expected operation stack
   */
  void testOperate(MockStateMachine &m, const IStatePtrList &expectedStack)
  {
    m.operate();
    Assert::IsTrue(expectedStack == m.operatedStack);

    // Reset operation stack
    m.operatedStack.clear();
  }
};
}
}
}