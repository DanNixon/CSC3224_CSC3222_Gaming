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
    class MockStateMachine : public StateMachine
    {
    public:
      int value;
    };
  }
}
}

#endif