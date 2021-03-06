/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
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
      /**
       * @copydoc StateMachine::operate
       */
      virtual void operate()
      {
        operatedStack.clear();
        StateMachine::operate();
      }

    public:
      int value;                   //!< Dummy value for triggering state transitions
      IStatePtrList entryStack;    //!< States that have had onEntry() called
      IStatePtrList exitStack;     //!< States that have had onExit() called
      IStatePtrList operatedStack; //!< States that have had onOperate() called
    };
  }
}
}

#endif
