/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "IController.h"
#include "MouseHandler.h"

namespace Engine
{
namespace Input
{
  /**
   * @class MouseController
   * @brief Represents a mouse control device.
   * @author Dan Nixon
   */
  class MouseController : public IController, public MouseHandler
  {
  public:
    MouseController(IControlScheme *parent, int screenX, int screenY);
    virtual ~MouseController();

    void setXMapping(size_t state);
    void setYMapping(size_t state);
    void setButtonMapping(Uint8 button, size_t state);

  private:
    virtual void handleButton(const SDL_MouseButtonEvent &e);
    virtual void handleMotion(const SDL_MouseMotionEvent &e);

    const int m_screenX; //!< Screen width
    const int m_screenY; //!< Screen height

    size_t *m_xMapping;                       //!< Analog state mapping for X position
    size_t *m_yMapping;                       //!< ANalog state mapping for Y position
    std::map<Uint8, size_t> m_buttonMappings; //!< Binary mappings for buttons
  };
}
}
