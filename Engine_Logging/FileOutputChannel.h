/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_LOGGING_IOUTPUTCHANNEL_H_
#define _ENGINE_LOGGING_IOUTPUTCHANNEL_H_

#include <string>

#include "LogLevel.h"

namespace Engine
{
namespace Logging
{
  /**
   * @class IOutputChannel
   * @brief Interface for output channels for log messages.
   * @author Dan Nixon
   */
  class IOutputChannel
  {
  public:
    IOutputChannel()
    {
    }

    virtual ~IOutputChannel()
    {
    }

    /**
     * @brief Opens the logging channel.
     * @return True if the channel was successfully opened.
     */
    virtual bool open()
    {
    }

    /**
     * @brief Closes the logging channel.
     * @return True if the channel was successfully closed.
     */
    virtual bool close()
    {
    }

    /**
     * @brief Sends a message to the logging channel.
     * @param level Verbosity level
     * @message Log message
     */
    virtual void sendMessage(LogLevel level, const std::string &message) = 0;
  };
}
}

#endif
