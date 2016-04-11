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
  /**
   * @brief Creates a new place cue ball state.
   * @param parent Parent state
   * @param machine The state machine to which this state belongs
   * @param simulation The simulation this state acts upon
   */
  PlaceCueBallState::PlaceCueBallState(IState *parent, StateMachine *machine, SnookerSimulation *simulation)
      : CompletableActionState("place_cue_ball", parent, machine)
      , m_simulation(simulation)
  {
  }

  PlaceCueBallState::~PlaceCueBallState()
  {
    resetMouseStartPosition();
  }

  /**
   * @copydoc CompletableActionState::testTransferFrom
   *
   * Moves to take shot state when the cue ball has been placed.
   */
  IState *PlaceCueBallState::testTransferFrom() const
  {
    if (m_completed)
      return m_parent->findState("take_shot").back();
    else
      return nullptr;
  }

  /**
   * @copydoc CompletableActionState::onEntry
   *
   * Resets recorded initial mouse poition and sets status line.
   */
  void PlaceCueBallState::onEntry(IState *last)
  {
    resetMouseStartPosition();
    m_simulation->statusLine->setText("Position cue ball");
  }

  /**
   * @copydoc CompletableActionState::onOperate
   */
  void PlaceCueBallState::onOperate()
  {
    if (m_simulation->menu->isMouseOver())
      return;

    // TODO: tidy this, initial position should not be needed

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
