#include "CppUnitTest.h"

#include "FakeStateMachine.h"
#include "FakeState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Simulation
{
namespace AI
{
namespace Test
{
TEST_CLASS(StateMachineTest)
{
public:
  TEST_METHOD(StateMachine_FullTest)
  {
    MockStateMachine sm;
    sm.value = 0;
  }
};
}
}
}