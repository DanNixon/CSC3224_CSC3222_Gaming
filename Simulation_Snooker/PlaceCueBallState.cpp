/**
 * @file
 * @author Dan Nixon
 */

#include "PlaceCueBallState.h"

using namespace Simulation::AI;
using namespace Engine::Maths;

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
      , m_placeStarted(false)
  {
  }

  PlaceCueBallState::~PlaceCueBallState()
  {
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
   * Sets the satus line accordingly.
   */
  void PlaceCueBallState::onEntry(IState *last)
  {
    CompletableActionState::onEntry(last);

    m_placeStarted = false;
    m_simulation->statusLine->setText("Position cue ball");
  }

  /**
   * @copydoc CompletableActionState::onOperate
   *
   * Handles controls for updating the position of the cue ball.
   */
  void PlaceCueBallState::onOperate()
  {
    // Do nothing if the mouse is hovered over the menu.
    if (m_simulation->menu->isMouseOver())
      return;

    if (!m_placeStarted && m_simulation->controls->state(S_TAKE_SHOT))
      m_placeStarted = true;

    if (m_placeStarted)
    {
      if (!m_simulation->controls->state(S_TAKE_SHOT))
      {
        // If mouse button is not pressed positioning is done
        m_completed = true;
      }
      else
      {
        // Update the position while the mouse button is held down
        Vector2 pos = Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
        m_simulation->balls[0]->setPosition(pos * 2000.0f);
      }
    }
  }
}
}
