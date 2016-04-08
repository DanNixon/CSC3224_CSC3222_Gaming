#include "CppUnitTest.h"

#include <Simulation_AI/IState.h>
#include <Simulation_AI/StateContainer.h>

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Simulation
{
namespace AI
{
namespace Test
{
TEST_CLASS(IStateTest)
{
public:
  TEST_METHOD(IState_branch)
  {
    IState * s1 = new IState("state1", nullptr, nullptr);
    IState * s12 = new IState("state1.2", s1, nullptr);
    IState * s121 = new IState("state1.2.1", s12, nullptr);

    Assert::IsTrue(IStatePtrList{ s1, s12, s121 } == s121->branch());
    Assert::IsTrue(IStatePtrList{ s1, s12, s121 } == s121->branch(false));
    Assert::IsTrue(IStatePtrList{ s121, s12, s1 } == s121->branch(true));
  }

  TEST_METHOD(IState_ClosestCommonAncestor)
  {
    IState * s1 = new IState("state1", nullptr, nullptr);
    IState * s11 = new IState("state1.1", s1, nullptr);
    IState * s12 = new IState("state1.2", s1, nullptr);
    IState * s121 = new IState("state1.2.1", s12, nullptr);
    IState * s122 = new IState("state1.2.2", s12, nullptr);

    Assert::IsTrue(s12 == IState::ClosestCommonAncestor(s122, s121));
    Assert::IsTrue(s1 == IState::ClosestCommonAncestor(s122, s11));
    Assert::IsTrue(s1 == IState::ClosestCommonAncestor(s121, s11));
    Assert::IsTrue(s1 == IState::ClosestCommonAncestor(s121, s1));
    Assert::IsTrue(s1 == IState::ClosestCommonAncestor(s1, s1));
  }

  TEST_METHOD(IState_ClosestCommonAncestor_noCommonAncestory)
  {
    IState * s1 = new IState("state1", nullptr, nullptr);
    IState * s11 = new IState("state1.1", s1, nullptr);

    IState * s2 = new IState("state2", nullptr, nullptr);
    IState * s22 = new IState("state2.2", s2, nullptr);
    IState * s221 = new IState("state2.2.1", s22, nullptr);
    IState * s222 = new IState("state2.2.2", s22, nullptr);

    Assert::IsTrue(nullptr == IState::ClosestCommonAncestor(s11, s221));
    Assert::IsTrue(nullptr == IState::ClosestCommonAncestor(s11, s22));
    Assert::IsTrue(nullptr == IState::ClosestCommonAncestor(s22, s1));
  }
};
}
}
}