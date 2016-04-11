/**
 * @file
 * @author Dan Nixon
 */

#include "TakeShotState.h"

using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  TakeShotState::TakeShotState(IState *parent, StateMachine *machine, SnookerSimulation *simulation)
      : CompletableActionState("take_shot", parent, machine)
      , m_simulation(simulation)
  {
  }

  TakeShotState::~TakeShotState()
  {
    resetMouseStartPosition();
  }

  IState *TakeShotState::testTransferFrom() const
  {
    if (m_completed)
      return m_parent->findState("wait_for_shot").back();
    else
      return nullptr;
  }

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
      if (m_simulation->balls[i]->collides() && shotState)
      {
        int points = m_simulation->balls[i]->points();
        shotState->setTargetBallPoints(points);
        m_simulation->statusLine->setText("Pot " + Ball::Info(points).first);
        return;
      }
    }
  }

  void TakeShotState::onExit(IState *next)
  {
    (void)next;
    m_simulation->balls[0]->setAcceleration(Engine::Maths::Vector2());
  }

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