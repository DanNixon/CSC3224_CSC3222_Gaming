/**
 * @file
 * @author Dan Nixon
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
  class PlaceCueBallState : public Simulation::AI::CompletableActionState
  {
  public:
    PlaceCueBallState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine,
                      SnookerSimulation *simulation)
        : CompletableActionState("place_cue_ball", parent, machine)
        , m_simulation(simulation)
    {
    }

    ~PlaceCueBallState()
    {
      resetMouseStartPosition();
    }

  protected:
    virtual IState *testTransferFrom() const
    {
      // Move to take shot when ball is placed
      if (m_completed)
        return m_parent->findState("take_shot").back();
      else
        return nullptr;
    }

    virtual void onEntry(IState *last)
    {
      // Reset recorded mouse start position
      resetMouseStartPosition();
    }

    virtual void onOperate()
    {
      if (m_simulation->menu->isMouseOver())
        return;

      // Handle controls for placing cue ball
      if (m_mouseStartPosition == nullptr)
      {
        if (m_simulation->controls->state(S_TAKE_SHOT))
        {
          // Record starting position of mouse
          m_mouseStartPosition = new Engine::Maths::Vector2(m_simulation->controls->analog(A_MOUSE_X),
                                                            m_simulation->controls->analog(A_MOUSE_Y));
        }
      }
      else
      {
        Engine::Maths::Vector2 newMousePosition = Engine::Maths::Vector2(m_simulation->controls->analog(A_MOUSE_X),
                                                                         m_simulation->controls->analog(A_MOUSE_Y));
        Engine::Maths::Vector2 deltaMouse = *m_mouseStartPosition - newMousePosition;

        // Clamp max acceleration to a sensible level
        float maxShotMagnitude = 0.5f;
        if (deltaMouse.length2() > (maxShotMagnitude * maxShotMagnitude))
          deltaMouse = Engine::Maths::VectorOperations::GetNormalised(deltaMouse) * maxShotMagnitude;

        if (!m_simulation->controls->state(S_TAKE_SHOT))
        {
          resetMouseStartPosition();
          m_completed = true;
        }
        else
        {
          m_simulation->balls[0]->setPosition(newMousePosition * 2000.0f);
        }
      }
    }

  private:
    inline void resetMouseStartPosition()
    {
      if (m_mouseStartPosition != nullptr)
        delete m_mouseStartPosition;
      m_mouseStartPosition = nullptr;
    }

  private:
    SnookerSimulation *m_simulation;
    Engine::Maths::Vector2 *m_mouseStartPosition;
  };
}
}

#endif