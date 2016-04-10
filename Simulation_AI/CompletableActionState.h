/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_COMPLETABLEACTIONSTATE_H_
#define _SIMULATION_AI_COMPLETABLEACTIONSTATE_H_

#include "FunctionalState.h"

namespace Simulation
{
namespace AI
{
  class CompletableActionState : public FunctionalState
  {
  public:
    CompletableActionState(const std::string &name, IState *parent, StateMachine *machine)
        : FunctionalState(name, parent, machine)
        , m_completed(false)
    {
    }

    bool completed() const
    {
      return m_completed;
    }

    void markAsComplete()
    {
      m_completed = true;
    }

  protected:
    virtual void onEntry(IState * last)
    {
      FunctionalState::onEntry(last);

      // Mark as not completed on state entry
      m_completed = false;
    }

  protected:
    bool m_completed; //!< Flag indicating completion
  };
}
}

#endif