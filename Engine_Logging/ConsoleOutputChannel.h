/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_LOGGING_CONSOLEOUTOUTCHANNEL_H_
#define _ENGINE_LOGGING_CONSOLEOUTPUTCHANNEL_H_

#include "IOutputChannel.h"

namespace Engine
{
namespace Logging
{
  /**
   * @class ConsoleOutputChannel
   * @brief Log output channel for printing to stdout.
   * @author Dan Nixon
   */
  class ConsoleOutputChannel : public IOutputChannel
  {
  public:
    ConsoleOutputChannel();
    virtual ~ConsoleOutputChannel();

    virtual void sendMessage(LogLevel level, const std::string &message);
  };
}
}

#endif
