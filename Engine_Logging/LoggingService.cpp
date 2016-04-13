/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "LoggingService.h"

namespace Engine
{
namespace Logging
{
  LoggingService::LoggingService()
  {
  }

  LoggingService::~LoggingService()
  {
    shutdown();
  }

  /**
   * @brief Closes and remove all output channels.
   */
  void LoggingService::shutdown()
  {
    log(LogLevel::TRACE, __FILE__, "Shutting down LoggingService");

    for (auto it = m_outputs.begin(); it != m_outputs.end(); ++it)
    {
      if (!(*it)->close())
        log(LogLevel::ERR, __FILE__, "Could not close a log output channel");
      delete *it;
    }
  }

  /**
   * @brief Adds an output channel to the logging service.
   * @param output Output channel to add
   */
  void LoggingService::addOutput(IOutputChannel *output)
  {
    m_outputs.push_back(output);
  }

  /**
   * @brief Removes an output channel from the logging service.
   * @param output Output channel to remove
   */
  void LoggingService::removeOutput(IOutputChannel *output)
  {
    auto it = std::find(m_outputs.begin(), m_outputs.end(), output);
    if (it != m_outputs.end())
    {
      if (!(*it)->close())
        log(LogLevel::ERR, __FILE__, "Could not close a log output channel");
      m_outputs.erase(it);
    }
  }

  /**
   * @brief Logs a message.
   * @param level Level at which the emssage is logged
   * @param loggerName Name of the logger logging the message
   * @param message Message text
   */
  void LoggingService::log(LogLevel level, const std::string &loggerName, const std::string &message)
  {
    std::string logMessage = LOG_LEVEL_NAMES.at(level) + " [" + loggerName + "] " + message;

    for (auto it = m_outputs.begin(); it != m_outputs.end(); ++it)
      (*it)->sendMessage(level, logMessage);
  }
}
}