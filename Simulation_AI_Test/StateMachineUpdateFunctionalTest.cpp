#include "CppUnitTest.h"

#include <Simulation_AI/FunctionalState.h>
#include <Simulation_AI/StateMachine.h>

#include "MockStateMachine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Simulation::AI;

// clang-format off
namespace Simulation
{
namespace AI
{
namespace Test
{
TEST_CLASS(StateMachineUpdateFunctionalTest)
{
public:
  TEST_METHOD(StateMachine_update_functional)
  {
    MockStateMachine m;
    m.value = 0;

    FunctionalState * s1 = new FunctionalState("state1", m.rootState(), &m);// , 5, "state2/state2.1");
    addStackFunctions(s1, m);
    s1->setTestTransferCase([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 5)
        return rm->rootState()->findState("state2/state2.1").back();
      else
        return nullptr;
    });

    FunctionalState * s11 = new FunctionalState("state1.1", s1, &m);// , 4, "state1/state1.2");
    addStackFunctions(s11, m);
    s11->setTestTransferCase([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 4)
        return rm->rootState()->findState("state1/state1.2").back();
      else
        return nullptr;
    });

    FunctionalState * s12 = new FunctionalState("state1.2", s1, &m);// , 3, "state1/state1.2/state1.2.1");
    addStackFunctions(s12, m);
    s12->setTestTransferCase([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 3)
        return rm->rootState()->findState("state1/state1.2/state1.2.1").back();
      else
        return nullptr;
    });

    FunctionalState * s121 = new FunctionalState("state1.2.1", s12, &m);// , 2, "state2/state2.1");
    addStackFunctions(s121, m);
    s121->setTestTransferCase([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 2)
        return rm->rootState()->findState("state2/state2.1").back();
      else
        return nullptr;
    });

    FunctionalState * s2 = new FunctionalState("state2", m.rootState(), &m);// , 6, "state1/state1.1");
    addStackFunctions(s2, m);
    s2->setTestTransferCase([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 6)
        return rm->rootState()->findState("state1/state1.1").back();
      else
        return nullptr;
    });

    FunctionalState * s21 = new FunctionalState("state2.1", s2, &m);// , 1, "state2");
    addStackFunctions(s21, m);
    s21->setTestTransferCase([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 1)
        return rm->rootState()->findState("state2").back();
      else
        return nullptr;
    });

    // Default activated state (1)
    s1->setActivation(true);
    m.m_entryStack.clear();
    m.m_exitStack.clear();

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
      Assert::AreEqual((size_t)0, m.m_entryStack.size());
      Assert::AreEqual((size_t)0, m.m_exitStack.size());
    }
    else
    {
      Assert::IsTrue(expectedExitStack == m.m_exitStack);
      Assert::IsTrue(expectedEntryStack == m.m_entryStack);
    }

    // Reset state entry and exit stacks
    m.m_entryStack.clear();
    m.m_exitStack.clear();
  }

  /**
   * @brief Performs operation test.
   * @param m Reference to the state machine under test
   * @param expectedStack Vector containing expected operation stack
   */
  void testOperate(MockStateMachine &m, const IStatePtrList &expectedStack)
  {
    m.operate();
    Assert::IsTrue(expectedStack == m.m_operatedStack);
  }

  /**
   * @brief Adds lambda functions used to record call stacks for testing.
   * @param state State to add to
   * @param m Reference to test state machine
   */
  void addStackFunctions(FunctionalState * state, MockStateMachine &m)
  {
    IStatePtrList &entry = m.m_entryStack;
    IStatePtrList &exit = m.m_exitStack;
    IStatePtrList &operate = m.m_operatedStack;

    state->setOnEntry([&entry](IState * s, StateMachine *){ entry.push_back(s); });
    state->setOnExit([&exit](IState * s, StateMachine *){ exit.push_back(s); });
    state->setOnOperate([&operate](IState * s, StateMachine *){ operate.push_back(s); });
  }
};
}
}
}