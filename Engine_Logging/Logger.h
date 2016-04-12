/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_LOGGING_LOGGER_H_
#define _ENGINE_LOGGING_LOGGER_H_

#include <string>

#include "LoggingService.h"

namespace Engine
{
namespace Logging
{
  class Logger
  {
  public:
    /**
     * @brief Creates a new logger.
     * @param name Name of the logger
     */
    Logger(const std::string &name)
        : m_name(name)
    {
    }

    /**
     * @brief Logs a message at TRACE level.
     * @param msg Log message
     */
    void trace(const std::string &msg)
    {
      LoggingService::Instance().log(LogLevel::TRACE, m_name, msg);
    }

    /**
     * @brief Logs a message at DEBUG level.
     * @param msg Log message
     */
    void debug(const std::string &msg)
    {
      LoggingService::Instance().log(LogLevel::DEBUG, m_name, msg);
    }

    /**
     * @brief Logs a message at INFO level.
     * @param msg Log message
     */
    void info(const std::string &msg)
    {
      LoggingService::Instance().log(LogLevel::INFO, m_name, msg);
    }

    /**
     * @brief Logs a message at WARN level.
     * @param msg Log message
     */
    void warn(const std::string &msg)
    {
      LoggingService::Instance().log(LogLevel::WARN, m_name, msg);
    }

    /**
     * @brief Logs a message at ERROR level.
     * @param msg Log message
     */
    void error(const std::string &msg)
    {
      LoggingService::Instance().log(LogLevel::ERR, m_name, msg);
    }

    /**
     * @brief Logs a message at CRITICAL level.
     * @param msg Log message
     */
    void critical(const std::string &msg)
    {
      LoggingService::Instance().log(LogLevel::CRITICAL, m_name, msg);
    }

  private:
    const std::string m_name; //!< Name of the logger
  };
}
}

#endif