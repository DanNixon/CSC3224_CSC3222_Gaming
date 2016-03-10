/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "IControlScheme.h"

#include <IMemoryManaged.h>

namespace Engine
{
namespace Input
{
  /**
   * @class IController
   * @brief Interface for a control device.
   * @author Dan Nixon
   */
  class IController : public Engine::Common::IMemoryManaged
  {
  public:
    /**
     * @brief Create a new control device.
     * @param parent Control scheme this device is used in
     */
    IController(IControlScheme *parent)
        : m_controlScheme(parent)
    {
    }

    virtual ~IController()
    {
    }

    /**
     * @brief Poll this device for changed inputs.
     */
    virtual void poll()
    {
    }

  protected:
    IControlScheme *m_controlScheme; //!< Control scheme this device is used in
  };
}
}
