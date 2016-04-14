/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "VSDebugOutputChannel.h"

#include <Windows.h>

namespace Engine
{
namespace Logging
{
  VSDebugOutputChannel::VSDebugOutputChannel()
  {
  }

  VSDebugOutputChannel::~VSDebugOutputChannel()
  {
  }

  /**
   * @copydoc IOutputChannel::sendMessage
   */
  void VSDebugOutputChannel::sendMessage(LogLevel level, const std::string &message)
  {
    if (level >= m_level)
      OutputDebugString((message + '\n').c_str());
  }
}
}