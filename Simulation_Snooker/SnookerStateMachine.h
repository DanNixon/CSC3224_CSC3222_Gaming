/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_SNOOKERSTATEMACHINE_H_
#define _SIMULATION_SNOOKER_SNOOKERSTATEMACHINE_H_

#include <Simulation_AI/CompletableActionState.h>
#include <Simulation_AI/StateMachine.h>

#include "PlaceCueBallState.h"
#include "PlayerState.h"
#include "TakeShotState.h"
#include "WaitForShotState.h"

namespace Simulation
{
namespace Snooker
{
  class SnookerSimulation;

  /**
   * @class SnookerStateMachine
   * @brief State machine for running a game of snooker on the simulator.
   * @author Dan Nixon
   */
  class SnookerStateMachine : public Simulation::AI::StateMachine
  {
  public:
    SnookerStateMachine(SnookerSimulation *simulation);
    virtual ~SnookerStateMachine();

    void initStates();

  private:
    void addPlayerStates(Simulation::AI::IState *parent, int playerNumber);

    void resetMouseStartPosition()
    {
      if (m_mouseStartPosition != nullptr)
        delete m_mouseStartPosition;
      m_mouseStartPosition = nullptr;
    }

    void updateControlTakeShot(Simulation::AI::CompletableActionState *state = nullptr);

  private:
    SnookerSimulation *m_simulation;

    Engine::Maths::Vector2 *m_mouseStartPosition;
  };
}
}

#endif
