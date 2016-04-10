/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_AI_FUNCTIONALSTATE_H_
#define _SIMULATION_AI_FUNCTIONALSTATE_H_

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
    typedef std::function<IState *(const IState *const, StateMachine *)> TransferFromFunc;
    typedef std::function<bool(const IState *const, StateMachine *)> TransferToFunc;
    typedef std::function<void(IState *, StateMachine *, IState *)> OnTransferFunc;
    typedef std::function<void(IState *, StateMachine *)> OnOperateFunc;

  public:
    /**
     * @copydoc IState::IState
     */
    FunctionalState(const std::string &name, IState *parent, StateMachine *machine)
        : IState(name, parent, machine)
    {
      m_testTransferFrom = [](const IState *const, StateMachine *) { return nullptr; };
      m_testTransferTo = [](const IState *const, StateMachine *) { return false; };
      m_onEntry = [](IState *, StateMachine *, IState *) {};
      m_onExit = [](IState *, StateMachine *, IState *) {};
      m_onOperate = [](IState *, StateMachine *) {};
    }

    virtual ~FunctionalState()
    {
    }

    void setTestTransferFrom(TransferFromFunc f)
    {
      m_testTransferFrom = f;
    }

    void setTestTransferTo(TransferToFunc f)
    {
      m_testTransferTo = f;
    }

    void setOnEntry(OnTransferFunc f)
    {
      m_onEntry = f;
    }

    void setOnExit(OnTransferFunc f)
    {
      m_onExit = f;
    }

    void setOnOperate(OnOperateFunc f)
    {
      m_onOperate = f;
    }

  protected:
    virtual IState *testTransferFrom() const
    {
      return m_testTransferFrom(this, m_machine);
    }

    virtual bool testTransferTo() const
    {
      return m_testTransferTo(this, m_machine);
    }

    virtual void onEntry(IState *last)
    {
      m_onEntry(this, m_machine, last);
    }

    virtual void onExit(IState *next)
    {
      m_onExit(this, m_machine, next);
    }

    virtual void onOperate()
    {
      m_onOperate(this, m_machine);
    }

  private:
    TransferFromFunc m_testTransferFrom;
    TransferToFunc m_testTransferTo;
    OnTransferFunc m_onEntry;
    OnTransferFunc m_onExit;
    OnOperateFunc m_onOperate;
  };
}
}

#endif