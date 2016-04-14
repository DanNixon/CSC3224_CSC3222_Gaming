/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "ConsoleOutputChannel.h"

#include <iostream>

namespace Engine
{
namespace Logging
{
  ConsoleOutputChannel::ConsoleOutputChannel()
  {
  }

  ConsoleOutputChannel::~ConsoleOutputChannel()
  {
  }

  /**
   * @copydoc IOutputChannel::sendMessage
   */
  void ConsoleOutputChannel::sendMessage(LogLevel level, const std::string &message)
  {
    if (level >= m_level)
      std::cout << message << std::endl;
  }
}
}