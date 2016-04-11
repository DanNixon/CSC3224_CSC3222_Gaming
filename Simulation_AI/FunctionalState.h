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
    /**
     * @typedef TransferFromFunc
     * @brief Function used in transfer from test.
     * @see FunctionalState::setTestTransferFrom
     */
    typedef std::function<IState *(const IState *const, StateMachine *)> TransferFromFunc;

    /**
     * @typedef TransferToFunc
     * @brief Function used in transfer to est.
     * @see FunctionalState::setTestTransferTo
     */
    typedef std::function<bool(const IState *const, StateMachine *)> TransferToFunc;

    /**
     * @typedef OnTransferFunc
     * @brief Function used for onEntry and onExit callbacks.
     * @see FunctionalState::setOnEntry()
     * @see FunctionalState::setOnExit()
     */
    typedef std::function<void(IState *, StateMachine *, IState *)> OnTransferFunc;

    /**
     * @typedef OnOperateFunc
     * @brief Function used for onOperate callbacks.
     * @see FunctionalState::setOnOperate()
     */
    typedef std::function<void(IState *, StateMachine *)> OnOperateFunc;

  public:
    /**
     * @copydoc IState::IState
     */
    FunctionalState(const std::string &name, IState *parent, StateMachine *machine)
        : IState(name, parent, machine)
    {
      m_testTransferFrom = [](const IState *const, StateMachine *)
      {
        return nullptr;
      };
      m_testTransferTo = [](const IState *const, StateMachine *)
      {
        return false;
      };
      m_onEntry = [](IState *, StateMachine *, IState *)
      {
      };
      m_onExit = [](IState *, StateMachine *, IState *)
      {
      };
      m_onOperate = [](IState *, StateMachine *)
      {
      };
    }

    virtual ~FunctionalState()
    {
    }

    /**
     * @brief Sets the callback function used to test if a state change should
     *        be triggered from this state when it is active.
     * @param f Callback function
     */
    void setTestTransferFrom(TransferFromFunc f)
    {
      m_testTransferFrom = f;
    }

    /**
     * @brief Sets the callback function used to test if this state should be
     *        transfered to when one of its siblings is active.
     * @param f Callback function
     */
    void setTestTransferTo(TransferToFunc f)
    {
      m_testTransferTo = f;
    }

    /**
     * @brief Sets the callback function that is called when this state is
     *        activated.
     * @param f Callback function
     */
    void setOnEntry(OnTransferFunc f)
    {
      m_onEntry = f;
    }

    /**
     * @brief Sets the callback function that is called when this state is
     *        deactivated.
     * @param f Callback function
     */
    void setOnExit(OnTransferFunc f)
    {
      m_onExit = f;
    }

    /**
     * @brief Sets the callback function used to perform operations associated
     *        with this state.
     * @param f Callback function
     */
    void setOnOperate(OnOperateFunc f)
    {
      m_onOperate = f;
    }

  protected:
    /**
     * @copydoc IState::testTransferFrom
     */
    virtual IState *testTransferFrom() const
    {
      return m_testTransferFrom(this, m_machine);
    }

    /**
     * @copydoc IState::testTransferTo
     */
    virtual bool testTransferTo() const
    {
      return m_testTransferTo(this, m_machine);
    }

    /**
     * @copydoc IState::onEntry
     */
    virtual void onEntry(IState *last)
    {
      m_onEntry(this, m_machine, last);
    }

    /**
     * @copydoc IState::onExit
     */
    virtual void onExit(IState *next)
    {
      m_onExit(this, m_machine, next);
    }

    /**
     * @copydoc IState::onOperate
     */
    virtual void onOperate()
    {
      m_onOperate(this, m_machine);
    }

  private:
    TransferFromFunc m_testTransferFrom; //!< Transfer from test function
    TransferToFunc m_testTransferTo;     //!< Transfer to test function
    OnTransferFunc m_onEntry;            //!< On entry callback
    OnTransferFunc m_onExit;             //!< On exit callback
    OnOperateFunc m_onOperate;           //!< On operate callback
  };
}
}

#endif
