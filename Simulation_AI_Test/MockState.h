/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATION_AI_TEST_MOCKSTATE_H_
#define _SIMULATION_AI_TEST_MOCKSTATE_H_

#include <Simulation_AI/IState.h>

#include "MockStateMachine.h"

namespace Simulation
{
namespace AI
{
  namespace Test
  {
    /**
     * @class MockState
     * @brief Mock state used for testing state machine.
     * @author Dan Nixon
     * @see MockStateMachine
     */
    class MockState : public IState
    {
    public:
      /**
       * @copydoc IState::IState
       * @param transferOn Value to transfer on
       * @param transferTo State to transfer to
       */
      MockState(const std::string &name, IState *parent, StateMachine *machine, int transferOn,
                const std::string &transferTo)
          : IState(name, parent, machine)
          , m_transferOn(transferOn)
          , m_transferTo(transferTo)
      {
      }

      /**
       * @copydoc IState::testTransferCase
       */
      IState *testTransferCase() const
      {
        MockStateMachine *machine = dynamic_cast<MockStateMachine *>(m_machine);

        int i = machine->value;

        if (machine->value == m_transferOn)
        {
          auto branch = m_machine->rootState()->findState(m_transferTo);
          return branch.back();
        }

        return nullptr;
      }

      /**
       * @copydoc IState::onEntry
       */
      virtual void onEntry()
      {
        MockStateMachine *machine = dynamic_cast<MockStateMachine *>(m_machine);
        machine->entryStack.push_back(this);
      }

      /**
       * @copydoc IState::onExit
       */
      virtual void onExit()
      {
        MockStateMachine *machine = dynamic_cast<MockStateMachine *>(m_machine);
        machine->exitStack.push_back(this);
      }

      /**
       * @copydoc IState::onOperate
       */
      virtual void onOperate()
      {
        MockStateMachine *machine = dynamic_cast<MockStateMachine *>(m_machine);
        machine->operatedStack.push_back(this);
      }

    private:
      int m_transferOn;
      std::string m_transferTo;
    };
  }
}
}

#endif
