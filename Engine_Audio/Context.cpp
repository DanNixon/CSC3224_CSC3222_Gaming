/**
 * @file
 * @author Dan Nixon
 */

#include "Context.h"

namespace Engine
{
  namespace Audio
  {
    Context::Context()
      : m_device(NULL)
      , m_context(NULL)
    {
    }

    Context::~Context()
    {
    }

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

    void Context::close()
    {
      alcMakeContextCurrent(NULL);
      alcDestroyContext(m_context);
      alcCloseDevice(m_device);
    }

    bool Context::isOpen() const
    {
      return (m_device && m_context);
    }
  }
}