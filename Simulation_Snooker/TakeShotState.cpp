/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
 */

#include "TakeShotState.h"

using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  /**
   * @brief Creates a new take shot state.
   * @param parent Parent state
   * @param machine The state machine to which this state belongs
   * @param simulation The simulation this state acts upon
   */
  TakeShotState::TakeShotState(IState *parent, StateMachine *machine, SnookerSimulation *simulation)
      : CompletableActionState("take_shot", parent, machine)
      , m_simulation(simulation)
  {
  }

  TakeShotState::~TakeShotState()
  {
    resetMouseStartPosition();
  }

  /**
   * @copydoc CompletableActionState::testTransferFrom
   */
  IState *TakeShotState::testTransferFrom() const
  {
    if (m_completed)
      return m_parent->findState("wait_for_shot").back();
    else
      return nullptr;
  }

  /**
   * @copydoc CompletableActionState::onEntry
   */
  void TakeShotState::onEntry(IState *last)
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
      m_simulation->statusLine->setText("Pot any colour");
      return;
    }

    // Players first shot in turn is either on red or the next colour in sequence if no reds are in play
    // i.e. whatever the lowest value ball in play is
    for (size_t i = 1; i < SnookerSimulation::NUM_BALLS; i++)
    {
      if (m_simulation->balls[i] != nullptr && m_simulation->balls[i]->collides() && shotState)
      {
        int points = m_simulation->balls[i]->points();
        shotState->setTargetBallPoints(points);
        m_simulation->statusLine->setText("Pot " + Ball::Info(points).first);
        return;
      }
    }
  }

  /**
   * @copydoc CompletableActionState::onExit
   *
   * Remove acceleration from ball, ensures acceleration is only applied for
   * one physics update.
   */
  void TakeShotState::onExit(IState *next)
  {
    (void)next;
    m_simulation->balls[0]->setAcceleration(Engine::Maths::Vector2());
  }

  /**
   * @copydoc CompletableActionState::onOperate
   */
  void TakeShotState::onOperate()
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
      Engine::Maths::Vector2 newMousePosition =
          Engine::Maths::Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
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
}
}
