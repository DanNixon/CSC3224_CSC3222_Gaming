/**
* @file
* @author Dan Nixon
*/

#ifndef _SIMULATION_AI_TEST_MOCKSTATEMACHINE_H_
#define _SIMULATION_AI_TEST_MOCKSTATEMACHINE_H_

#include <Simulation_AI/StateMachine.h>

namespace Simulation
{
namespace AI
{
  namespace Test
  {
    /**
     * @class MockStateMachine
     * @brief Mock state machine used for testing with MockState.
     * @author Dan Nixon
     * @see MockState
     */
    class MockStateMachine : public StateMachine
    {
    public:
      virtual void operate()
      {
        m_operatedStack.clear();
        StateMachine::operate();
      }

    public:
      int value;                     //!< Dummy value for triggering state transitions
      IStatePtrList m_entryStack;    //!< States that have had onEntry() called
      IStatePtrList m_exitStack;     //!< States that have had onExit() called
      IStatePtrList m_operatedStack; //!< States that have had onOperate() called
    };
  }
}
}

#endif
