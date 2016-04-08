/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_FUNCTIONALSTATE_H_
#define _SIMULATION_AI_FUNCIIONALSTATE_H_

#include "IState.h"

#include <functional>

namespace Simulation
{
namespace AI
{
  /**
   * @class FunctionalState
   * @brief State that can have operations assigned via function pointers,
   *        functors and lambdas.
   * @author Dan Nixon
   */
  class FunctionalState : public IState
  {
  public:
    typedef std::function<IState *(const IState *const, StateMachine *)> TransferCaseFunc;
    typedef std::function<void(IState *, StateMachine *)> HandlerFunc;

  public:
    /**
     * @copydoc IState::IState
     */
    FunctionalState(const std::string &name, IState *parent, StateMachine *machine)
        : IState(name, parent, machine)
    {
      m_testTransferCase = [](const IState *const, StateMachine *) { return nullptr; };
      m_onEntry = [](IState *, StateMachine *) {};
      m_onExit = [](IState *, StateMachine *) {};
      m_onOperate = [](IState *, StateMachine *) {};
    }

    virtual ~FunctionalState()
    {
    }

    void setTestTransferCase(TransferCaseFunc f)
    {
      m_testTransferCase = f;
    }

    void setOnEntry(HandlerFunc f)
    {
      m_onEntry = f;
    }

    void setOnExit(HandlerFunc f)
    {
      m_onExit = f;
    }

    void setOnOperate(HandlerFunc f)
    {
      m_onOperate = f;
    }

  protected:
    virtual IState *testTransferCase() const
    {
      return m_testTransferCase(this, m_machine);
    }

    virtual void onEntry()
    {
      m_onEntry(this, m_machine);
    }

    virtual void onExit()
    {
      m_onExit(this, m_machine);
    }

    virtual void onOperate()
    {
      m_onOperate(this, m_machine);
    }

  private:
    TransferCaseFunc m_testTransferCase;
    HandlerFunc m_onEntry;
    HandlerFunc m_onExit;
    HandlerFunc m_onOperate;
  };
}
}

#endif