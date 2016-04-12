/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

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
#ifndef DOXYGEN_SKIP
TEST_CLASS(StateMachineUpdateFunctionalTest)
{
public:
  TEST_METHOD(StateMachine_update_functional)
  {
    MockStateMachine m;
    m.value = 0;

    FunctionalState * s1 = new FunctionalState("state1", m.rootState(), &m);
    addStackFunctions(s1, m);
    s1->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 5)
        return rm->rootState()->findState("state2/state2.1").back();
      else
        return nullptr;
    });

    FunctionalState * s11 = new FunctionalState("state1.1", s1, &m);
    addStackFunctions(s11, m);
    s11->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 4)
        return rm->rootState()->findState("state1/state1.2").back();
      else
        return nullptr;
    });

    FunctionalState * s12 = new FunctionalState("state1.2", s1, &m);
    addStackFunctions(s12, m);
    s12->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 3)
        return rm->rootState()->findState("state1/state1.2/state1.2.1").back();
      else
        return nullptr;
    });

    FunctionalState * s121 = new FunctionalState("state1.2.1", s12, &m);
    addStackFunctions(s121, m);
    s121->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 2)
        return rm->rootState()->findState("state2/state2.1").back();
      else
        return nullptr;
    });

    FunctionalState * s2 = new FunctionalState("state2", m.rootState(), &m);
    addStackFunctions(s2, m);
    s2->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 6)
        return rm->rootState()->findState("state1/state1.1").back();
      else
        return nullptr;
    });

    FunctionalState * s21 = new FunctionalState("state2.1", s2, &m);
    addStackFunctions(s21, m);
    s21->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 1)
        return rm->rootState()->findState("state2").back();
      else
        return nullptr;
    });

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

  TEST_METHOD(StateMachine_update_forward_functional)
  {
    MockStateMachine m;
    IStatePtrList &entry = m.entryStack;
    m.value = 0;

    FunctionalState * s1 = new FunctionalState("state1", m.rootState(), &m);
    addStackFunctions(s1, m);
    s1->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 1)
        return rm->rootState()->findState("state1/state1.1").back();
      else
        return nullptr;
    });

    FunctionalState * s11 = new FunctionalState("state1.1", s1, &m);
    addStackFunctions(s11, m);
    // Test auto activating a child state
    s11->setOnEntry([&entry](IState * s, StateMachine *rm, IState *){
      entry.push_back(s);
      rm->rootState()->findState("state1/state1.1/state1.1.1").back()->setActivation(true, s);
    });

    FunctionalState * s111 = new FunctionalState("state1.1.1", s11, &m);
    addStackFunctions(s111, m);

    FunctionalState * s12 = new FunctionalState("state1.2", s1, &m);
    addStackFunctions(s12, m);
    s12->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 3)
        return rm->rootState()->findState("state1").back();
      else
        return nullptr;
    });

    // Default activated state (1.2)
    s12->setActivation(true);
    m.entryStack.clear();
    m.exitStack.clear();

    testTransfer(m, 0, "state1/state1.2");

    // Operate on 1.2
    testOperate(m, { s1, s12 });

    // Transfer from 1.2 to 1
    testTransfer(m, 3, "state1", { s12 }, { });

    // Operate on 1
    testOperate(m, { s1 });

    // Transfer from 1 to 1.1.1 (via 1.1 as forwarding state)
    testTransfer(m, 1, "state1/state1.1/state1.1.1", { }, { s11, s111 });
  }

  TEST_METHOD(StateMachine_update_to_functional)
  {
    MockStateMachine m;
    IStatePtrList &entry = m.entryStack;
    m.value = 0;

    FunctionalState * s1 = new FunctionalState("state1", m.rootState(), &m);
    addStackFunctions(s1, m);
    s1->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 1)
        return rm->rootState()->findState("state1/state1.1").back();
      else
        return nullptr;
    });

    FunctionalState * s11 = new FunctionalState("state1.1", s1, &m);
    addStackFunctions(s11, m);

    FunctionalState * s12 = new FunctionalState("state1.2", s1, &m);
    addStackFunctions(s12, m);
    // Test transfer to this state from sibling states
    s12->setTestTransferTo([](const IState * const s, StateMachine * rm) -> bool {
      return true;
    });
    s12->setTestTransferFrom([&m](const IState * const s, StateMachine * rm) -> IState *{
      if (m.value == 3)
        return rm->rootState()->findState("state1").back();
      else
        return nullptr;
    });

    // Default activated state (1.2)
    s12->setActivation(true);
    m.entryStack.clear();
    m.exitStack.clear();

    testTransfer(m, 0, "state1/state1.2");

    // Operate on 1.2
    testOperate(m, { s1, s12 });

    // Transfer from 1.2 to 1
    testTransfer(m, 3, "state1", { s12 }, {});

    // Operate on 1
    testOperate(m, { s1 });

    // Transfer from 1 to 1.1
    testTransfer(m, 1, "state1/state1.1", {}, { s11 });

    // Operate on 1.1
    testOperate(m, { s1, s11 });

    // Transfer from 1.1 to 1.2 (from being on a siblimg of 1.2)
    testTransfer(m, -1, "state1/state1.2", { s11 }, { s12 });

    // Operate on 1.2
    testOperate(m, { s1, s12 });
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

  /**
   * @brief Adds lambda functions used to record call stacks for testing.
   * @param state State to add to
   * @param m Reference to test state machine
   */
  void addStackFunctions(FunctionalState * state, MockStateMachine &m)
  {
    IStatePtrList &entry = m.entryStack;
    IStatePtrList &exit = m.exitStack;
    IStatePtrList &operate = m.operatedStack;

    state->setOnEntry([&entry](IState * s, StateMachine *, IState *){ entry.push_back(s); });
    state->setOnExit([&exit](IState * s, StateMachine *, IState *){ exit.push_back(s); });
    state->setOnOperate([&operate](IState * s, StateMachine *){ operate.push_back(s); });
  }
};
#endif /* DOXYGEN_SKIP */
}
}
}
