/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_TAKESHOTSTATE_H_
#define _SIMULATION_SNOOKER_TAKESHOTSTATE_H_

#include <string>

#include <Engine_Graphics/LineMesh.h>
#include <Engine_Maths/VectorOperations.h>

#include <Simulation_AI/CompletableActionState.h>
#include <Simulation_AI/FunctionalState.h>
#include <Simulation_AI/IState.h>
#include <Simulation_AI/StateMachine.h>

#include "SnookerControls.h"
#include "SnookerSimulation.h"
#include "WaitForShotState.h"

namespace Simulation
{
namespace Snooker
{
  class TakeShotState : public Simulation::AI::CompletableActionState
  {
  public:
    TakeShotState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine, SnookerSimulation *simulation)
        : CompletableActionState("take_shot", parent, machine)
        , m_simulation(simulation)
    {
    }

    virtual ~TakeShotState()
    {
      resetMouseStartPosition();
    }

  protected:
    virtual IState *testTransferFrom() const
    {
      if (m_completed)
        return m_parent->findState("wait_for_shot").back();
      else
        return nullptr;
    }

    virtual void onExit(IState *next)
    {
      (void)next;
      m_simulation->balls[0]->setAcceleration(Engine::Maths::Vector2());
    }

    virtual void onEntry(IState *last)
    {
      CompletableActionState::onEntry(last);
      resetMouseStartPosition();

      WaitForShotState *shotState = dynamic_cast<WaitForShotState *>(m_parent->findState("wait_for_shot").back());
      if (shotState == nullptr)
        return;

      // If players last shot in turn was a red then now they hit any colour
      if (shotState->lastPotted() != nullptr && shotState->lastPotted()->points() == 1)
      {
        shotState->setTargetBallPoints(0);
        return;
      }

      // Players first shot in turn is either on red or the next colour in sequence if no reds are in play
      // i.e. whatever the lowest value ball in play is
      for (size_t i = 1; i < SnookerSimulation::NUM_BALLS; i++)
      {
        if (m_simulation->balls[i]->collides() && shotState)
        {
          shotState->setTargetBallPoints(m_simulation->balls[i]->points());
          return;
        }
      }
    }

    virtual void onOperate()
    {
      if (m_simulation->menu->isMouseOver())
        return;

      // Mouse clicks (to take shots)
      if (m_mouseStartPosition == nullptr)
      {
        if (m_simulation->controls->state(S_TAKE_SHOT))
        {
          // Record starting position of mouse
          m_mouseStartPosition = new Engine::Maths::Vector2(m_simulation->controls->analog(A_MOUSE_X),
                                                            m_simulation->controls->analog(A_MOUSE_Y));
          static_cast<Engine::Graphics::LineMesh *>(m_simulation->shotAimLine->mesh())->setTo(Engine::Maths::Vector3());
          m_simulation->shotAimLine->setActive(true);
        }
        else
        {
          m_simulation->balls[0]->setAcceleration(Engine::Maths::Vector2());
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
          m_simulation->shotAimLine->setActive(false);
          m_simulation->balls[0]->setAcceleration(deltaMouse);
          resetMouseStartPosition();
          m_completed = true;
        }
        else
        {
          static_cast<Engine::Graphics::LineMesh *>(m_simulation->shotAimLine->mesh())->setTo(deltaMouse * 1000.0f);
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