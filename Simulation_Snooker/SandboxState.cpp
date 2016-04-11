/**
 * @file
 * @author Dan Nixon
 */

#include "SandboxState.h"

using namespace Simulation::AI;
using namespace Engine::Maths;
using namespace Engine::Graphics;

namespace Simulation
{
namespace Snooker
{
  SandboxState::SandboxState(IState *parent, StateMachine *machine, SnookerSimulation *simulation)
      : WaitForShotState(parent, machine, simulation, "sandbox")
  {
  }

  SandboxState::~SandboxState()
  {
    resetMouseStartPosition();
  }

  /**
   * @copydoc WaitForShotState::testTransferFrom
   */
  IState *SandboxState::testTransferFrom() const
  {
    if (m_simulation->controls->state(S_MODE_CHANGE))
    {
      m_simulation->controls->setState(S_MODE_CHANGE, false);
      return m_machine->rootState()->findState("game").back();
    }
    return nullptr;
  }

  /**
   * @copydoc WaitForShotState::onEntry
   */
  void SandboxState::onEntry(IState *last)
  {
    m_simulation->statusLine->setText("Sandbox");
  }

  /**
   * @copydoc WaitForShotState::onOperate
   */
  void SandboxState::onOperate()
  {
    WaitForShotState::onOperate();

    if (m_simulation->menu->isMouseOver())
      return;

    // Mouse clicks (to take shots)
    if (m_mouseStartPosition == nullptr)
    {
      if (m_simulation->controls->state(S_TAKE_SHOT))
      {
        // Record starting position of mouse
        m_mouseStartPosition =
            new Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
        static_cast<LineMesh *>(m_simulation->shotAimLine->mesh())->setTo(Vector3());
        m_simulation->shotAimLine->setActive(true);
      }
      else
      {
        m_simulation->balls[0]->setAcceleration(Vector2());
      }
    }
    else
    {
      Vector2 newMousePosition =
          Vector2(m_simulation->controls->analog(A_MOUSE_X), m_simulation->controls->analog(A_MOUSE_Y));
      Vector2 deltaMouse = *m_mouseStartPosition - newMousePosition;

      // Clamp max acceleration to a sensible level
      float maxShotMagnitude = 0.5f;
      if (deltaMouse.length2() > (maxShotMagnitude * maxShotMagnitude))
        deltaMouse = VectorOperations::GetNormalised(deltaMouse) * maxShotMagnitude;

      if (!m_simulation->controls->state(S_TAKE_SHOT))
      {
        m_simulation->shotAimLine->setActive(false);
        m_simulation->balls[0]->setAcceleration(deltaMouse);
        resetMouseStartPosition();
      }
      else
      {
        static_cast<LineMesh *>(m_simulation->shotAimLine->mesh())->setTo(deltaMouse * 1000.0f);
      }
    }
  }
}
}
