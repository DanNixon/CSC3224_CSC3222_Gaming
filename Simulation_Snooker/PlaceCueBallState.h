/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#ifndef _SIMULATION_SNOOKER_PLACECUEBALLSTATE_H_
#define _SIMULATION_SNOOKER_PLACECUEBALLSTATE_H_

#include <string>

#include <Engine_Graphics/LineMesh.h>
#include <Engine_Maths/VectorOperations.h>

#include <Simulation_AI/CompletableActionState.h>
#include <Simulation_AI/IState.h>
#include <Simulation_AI/StateMachine.h>

#include "SnookerControls.h"
#include "SnookerSimulation.h"

namespace Simulation
{
namespace Snooker
{
  /**
   * @class PlaceCueBallState
   * @brief State used during placement of the cue ball.
   * @author Dn Nixon
   */
  class PlaceCueBallState : public Simulation::AI::CompletableActionState
  {
  public:
    PlaceCueBallState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine,
                      SnookerSimulation *simulation);
    virtual ~PlaceCueBallState();

  protected:
    virtual IState *testTransferFrom() const;
    virtual void onEntry(IState *last);
    virtual void onOperate();

  private:
    SnookerSimulation *m_simulation; //!< Simulaion state is acting on
    bool m_placeStarted;             //!< Flag indicating that positioning of the cue ball has started
  };
}
}

#endif
