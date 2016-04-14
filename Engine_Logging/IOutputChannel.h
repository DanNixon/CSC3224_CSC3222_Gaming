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
    /**
     * @brief Creates a new log output channel.
     *
     * Default log verbosity level is INFO.
     */
    IOutputChannel()
        : m_level(LogLevel::INFO)
    {
    }

    virtual ~IOutputChannel()
    {
    }

    /**
     * @brief Sets the verbosity level of this channel.
     * @param level Log level
     */
    inline void setLevel(LogLevel level)
    {
      m_level = level;
    }

    /**
     * @brief Gets the verbosity level for this channel.
     * @return Log level
     */
    inline LogLevel level() const
    {
      return m_level;
    }

    /**
     * @brief Opens the logging channel.
     * @return True if the channel was successfully opened.
     */
    virtual bool open()
    {
      return true;
    }

    /**
     * @brief Closes the logging channel.
     * @return True if the channel was successfully closed.
     */
    virtual bool close()
    {
      return true;
    }

    /**
     * @brief Sends a message to the logging channel.
     * @param level Verbosity level
     * @param message Log message
     */
    virtual void sendMessage(LogLevel level, const std::string &message) = 0;

  protected:
    LogLevel m_level; //!< Verbosity level
  };
}
}

#endif
