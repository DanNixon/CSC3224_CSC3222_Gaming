/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#pragma once

#include "IControlScheme.h"

#include <Engine_ResourceManagment/IMemoryManaged.h>

namespace Engine
{
namespace Input
{
  /**
   * @class IController
   * @brief Interface for a control device.
   * @author Dan Nixon
   */
  class IController : public Engine::ResourceManagment::IMemoryManaged
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
