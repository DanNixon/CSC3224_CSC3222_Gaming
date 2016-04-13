/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_LOGGING_LOGLEVEL_H_
#define _ENGINE_LOGGING_LOGLEVEL_H_

#include <map>

namespace Engine
{
namespace Logging
{
  /**
   * @enum LogLevel
   * @brief Represents logging verbosity levels.
   * @author Dan Nixon
   */
  enum class LogLevel
  {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERR,
    CRITICAL,
    OFF
  };

  /**
   * @var LOG_LEVEL_NAMES
   * @brief Map of log levels to friendly strings.
   */
  const std::map<LogLevel, std::string> LOG_LEVEL_NAMES{
      {LogLevel::TRACE, "TRACE"}, {LogLevel::DEBUG, "DEBUG"},       {LogLevel::INFO, "INFO"}, {LogLevel::WARN, "WARN"},
      {LogLevel::ERR, "ERROR"},   {LogLevel::CRITICAL, "CRITICAL"}, {LogLevel::OFF, ""}};
}
}

#endif
