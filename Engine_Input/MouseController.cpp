/**
 * @file
 * @author Dan Nixon
 */

#include "MouseController.h"

namespace Engine
{
namespace Input
{
  /**
   * @copydoc IController::IController
   * @param screenX Screen width
   * @param screenY Screen height
   */
  MouseController::MouseController(IControlScheme *parent, int screenX, int screenY)
      : IController(parent)
      , m_screenX(screenX)
      , m_screenY(screenY)
      , m_xMapping(NULL)
      , m_yMapping(NULL)
  {
  }

  MouseController::~MouseController()
  {
    if (m_xMapping)
      delete m_xMapping;

    if (m_yMapping)
      delete m_yMapping;
  }

  /**
   * @brief Sets the state mapping for the X position.
   * @param state Analog state ID
   */
  void MouseController::setXMapping(size_t state)
  {
    if (m_xMapping)
      delete m_xMapping;

    m_xMapping = new size_t(state);
  }

  /**
   * @brief Sets the state mapping for the Y position.
   * @param state Analog state ID
   */
  void MouseController::setYMapping(size_t state)
  {
    if (m_yMapping)
      delete m_yMapping;

    m_yMapping = new size_t(state);
  }

  /**
   * @brief Sets the state mapping for a given button.
   * @param button Button ID
   * @param state State ID
   */
  void MouseController::setButtonMapping(Uint8 button, size_t state)
  {
    m_buttonMappings[button] = state;
  }

  /**
   * @copydoc MouseHandler::handleButton
   */
  void MouseController::handleButton(const SDL_MouseButtonEvent &e)
  {
    auto it = m_buttonMappings.find(e.button);
    if (it != m_buttonMappings.end())
      m_controlScheme->setState(it->second, e.type == SDL_MOUSEBUTTONDOWN);
  }

  /**
   * @copydoc MouseHandler::handleMotion
   */
  void MouseController::handleMotion(const SDL_MouseMotionEvent &e)
  {
    auto relScrn = MouseHandler::GetNormalisedPos(e, m_screenX, m_screenY);

    if (m_xMapping)
      m_controlScheme->setAnalog(*m_xMapping, relScrn.first);

    if (m_yMapping)
      m_controlScheme->setAnalog(*m_yMapping, relScrn.second);
  }
}
}
