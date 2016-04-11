/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#ifndef _SIMULATION_SNOOKER_TAKESHOTSTATE_H_
#define _SIMULATION_SNOOKER_TAKESHOTSTATE_H_

#include <string>

#include <Engine_Graphics/LineMesh.h>
#include <Engine_Maths/VectorOperations.h>

#include <Simulation_AI/CompletableActionState.h>
#include <Simulation_AI/StateMachine.h>

#include "SnookerControls.h"
#include "SnookerSimulation.h"
#include "WaitForShotState.h"

namespace Simulation
{
namespace Snooker
{
  /**
   * @class TakeShotState
   * @brief STate used for taking a shot in a game.
   * @author Dan Nixon
   */
  class TakeShotState : public Simulation::AI::CompletableActionState
  {
  public:
    TakeShotState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine, SnookerSimulation *simulation);
    virtual ~TakeShotState();

  protected:
    virtual IState *testTransferFrom() const;
    virtual void onExit(IState *next);
    virtual void onEntry(IState *last);
    virtual void onOperate();

  private:
    /**
     * @brief Resets the recorded initial mouse position.
     */
    inline void resetMouseStartPosition()
    {
      if (m_mouseStartPosition != nullptr)
        delete m_mouseStartPosition;
      m_mouseStartPosition = nullptr;
    }

  private:
    SnookerSimulation *m_simulation;              //!< Simulaion state is acting on
    Engine::Maths::Vector2 *m_mouseStartPosition; //!< Position of mouse pointer at start of click and drag
  };
}
}

#endif
