/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_LOGGING_VSDEBUGOUTOUTCHANNEL_H_
#define _ENGINE_LOGGING_VSDEBUGOUTOUTCHANNEL_H_

#include "IOutputChannel.h"

#include <Windows.h>

namespace Engine
{
namespace Logging
{
  /**
   * @class VSDebugOutputChannel
   * @brief Log output channel for printing to Visual Studio debug window.
   * @author Dan Nixon
   */
  class VSDebugOutputChannel : public IOutputChannel
  {
  public:
    VSDebugOutputChannel()
    {
    }

    virtual ~VSDebugOutputChannel()
    {
    }

    /**
     * @copydoc IOutputChannel::sendMessage
     */
    virtual void sendMessage(LogLevel level, const std::string &message)
    {
      if (level >= m_level)
        OutputDebugString(message.c_str());
    }
  };
}
}

#endif
