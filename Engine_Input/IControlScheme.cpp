/**
 * @file
 * @author Dan Nixon
 */

#include "IControlScheme.h"

#include <Engine_Common/Game.h>
#include <Engine_Common/IEventHandler.h>

#include "IController.h"

#include <iostream>

using namespace Engine::Common;

namespace Engine
{
namespace Input
{
  /**
   * @brief Create a new control scheme instance.
   * @param game Game instance this scheme is used in
   */
  IControlScheme::IControlScheme(Game *game)
      : m_game(game)
  {
    setAnalogDeadbands(0.0f, 0.0f);
    setAnalogLimits(-1.0f, 1.0f);
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

  void IControlScheme::setAnalogLimits(float minValue, float maxValue)
  {
    m_analogLimits[0] = minValue;
    m_analogLimits[1] = maxValue;
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
    setState(state, !m_state[state]);
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
    else if (value > (m_analogLimits[1] - m_analogDeadbands[2]))
      value = m_analogLimits[1];
    else if (value < (m_analogLimits[0] + m_analogDeadbands[0]))
      value = m_analogLimits[0];

    m_analogs[state] = value;
  }
}
}
