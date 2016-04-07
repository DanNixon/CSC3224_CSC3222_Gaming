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
        MockState(const std::string &name, State *parent, int transferOn, const std::string &transferTo)
          : State(name, parent)
          , m_transferOn(transferOn)
          , m_transferTo(transferTo)
        {
        }

        State * testTransferCase() const
        {
          int v = dynamic_cast<MockStateMachine *>(m_machine)->value;
          if (v == m_transferOn)
          {
            // TODO
          }
        }

      private:
        int m_transferOn;
        std::string m_transferTo;
      };
    }
  }
}

#endif