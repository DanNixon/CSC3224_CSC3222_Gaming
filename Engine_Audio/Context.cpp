/**
 * @file
 * @author Dan Nixon
 */

#include "Context.h"

namespace Engine
{
namespace Audio
{
  /**
   * @brief Creates a new context container.
   */
  Context::Context()
      : m_device(NULL)
      , m_context(NULL)
  {
  }

  Context::~Context()
  {
  }

  /**
   * @brief Creates the context and opens the default audio device.
   * @return True on success
   */
  bool Context::open()
  {
    if (isOpen())
      return true;

    // Open the default device
    m_device = alcOpenDevice(NULL);
    if (!m_device)
      return false;

    // Create context
    m_context = alcCreateContext(m_device, NULL);

    // Activate context
    return alcMakeContextCurrent(m_context) == ALC_TRUE;
  }

  /**
   * @brief Closes the device and removes the context.
   */
  void Context::close()
  {
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
  }

  /**
   * @brief Tests for an open device and context.
   * @return True if open.
   */
  bool Context::isOpen() const
  {
    return (m_device && m_context);
  }
}
}
