/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATION_AI_TEST_FAKESTATE_H_
#define _SIMULATION_AI_TEST_FAKESTATE_H_

#include <Simulation_AI/State.h>

#include "FakeStateMachine.h"

namespace Simulation
{
namespace AI
{
  namespace Test
  {
    class MockState : public State
    {
    public:
      MockState(const std::string &name, State *parent, StateMachine *machine, int transferOn,
                const std::string &transferTo)
          : State(name, parent, machine)
          , m_transferOn(transferOn)
          , m_transferTo(transferTo)
      {
      }

      State *testTransferCase() const
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

    private:
      int m_transferOn;
      std::string m_transferTo;
    };
  }
}
}

#endif