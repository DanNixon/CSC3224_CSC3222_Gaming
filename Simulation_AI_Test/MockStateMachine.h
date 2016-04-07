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
      int value; //!< Dummy value for triggering state transitions
    };
  }
}
}

#endif
