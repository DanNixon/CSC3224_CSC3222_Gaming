/**
 * @file
 * @author Dan Nixon
 */

#include "IControlScheme.h"

#include <Game.h>
#include <IEventHandler.h>

#include "IController.h"

using namespace Engine::Common;

namespace Engine
{
namespace Input
{
  /**
   * @brief Create a new control scheme instance.
   */
  IControlScheme::IControlScheme()
  {
    setAnalogDeadbands(0.0f, 0.0f);
  }

  IControlScheme::~IControlScheme()
  {
  }

  /**
   * @brief Adds a controler to the scheme.
   * @param controller Controller to add
   */
  void IControlScheme::addController(IController *controller)
  {
    m_controllers.push_back(controller);
  }

  /**
   * @brief Polls for input changes.
   *
   * Required if any controllers use polling rather than events.
   */
  void IControlScheme::poll()
  {
    for (auto it = m_controllers.begin(); it != m_controllers.end(); ++it)
      (*it)->poll();
  }

  /**
   * @brief Gets a binary state.
   * @param s State ID
   * @return Value of state
   */
  bool IControlScheme::state(size_t s) const
  {
    return m_state[s];
  }

  /**
   * @brief Tests if an analog ID is known (has been set at least once).
   * @param a Analog state ID
   * @return True if analog state has a value
   */
  bool IControlScheme::hasAnalog(size_t a) const
  {
    return m_analogs.find(a) != m_analogs.end();
  }

  /**
   * @brief Gets the value of an analog state.
   * @param a Analog state ID
   * @return Value of analog state
   */
  float IControlScheme::analog(size_t a) const
  {
    auto it = m_analogs.find(a);
    if (it == m_analogs.end())
      return 0.0f;
    return (*it).second;
  }

  /**
   * @brief Sets deadbands for analog states.
   * @param deadbandCentre Centre deadband
   * @param deadbandLimit High/low deadbands
   */
  void IControlScheme::setAnalogDeadbands(float deadbandCentre, float deadbandLimit)
  {
    m_analogDeadbands[0] = deadbandLimit;
    m_analogDeadbands[1] = deadbandCentre;
    m_analogDeadbands[2] = deadbandLimit;
  }

  /**
   * @brief Sets the value of a binary state.
   * @param state State ID
   * @param active Value of state
   */
  void IControlScheme::setState(size_t state, bool active)
  {
    m_state.set(state, active);
  }

  /**
   * @brief Flips/toggles the value of a binary state.
   * @param state State ID
   */
  void IControlScheme::flipState(size_t state)
  {
    m_state.flip(state);
  }

  /**
   * @brief Sets the value of an analog state.
   * @param state Analog state ID
   * @param value Value of state
   */
  void IControlScheme::setAnalog(size_t state, float value)
  {
    if (value >= -m_analogDeadbands[1] && value <= m_analogDeadbands[1])
      value = 0.0f;
    else if (value > (1.0f - m_analogDeadbands[2]))
      value = 1.0f;
    else if (value < (-1.0f + m_analogDeadbands[0]))
      value = -1.0f;

    m_analogs[state] = value;
  }
}
}
