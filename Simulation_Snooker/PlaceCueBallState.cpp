/**
 * @file
 * @author Dan Nixon
 */

#include "PlaceCueBallState.h"

using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  PlaceCueBallState::PlaceCueBallState(IState *parent, StateMachine *machine, SnookerSimulation *simulation)
      : CompletableActionState("place_cue_ball", parent, machine)
      , m_simulation(simulation)
  {
  }

  PlaceCueBallState::~PlaceCueBallState()
  {
    resetMouseStartPosition();
  }

  IState *PlaceCueBallState::testTransferFrom() const
  {
    // Move to take shot when ball is placed
    if (m_completed)
      return m_parent->findState("take_shot").back();
    else
      return nullptr;
  }

  void PlaceCueBallState::onEntry(IState *last)
  {
    // Reset recorded mouse start position
    resetMouseStartPosition();

    m_simulation->statusLine->setText("Position cue ball");
  }

  void PlaceCueBallState::onOperate()
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
      Engine::Maths::Vector2 newMousePosition =
          Engine::Maths::Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
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
}
}